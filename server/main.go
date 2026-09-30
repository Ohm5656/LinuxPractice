package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"time"
)

type SensorData struct {
	SensorID    int     `json:"sensor_id"`
	Sequence    int     `json:"sequence"`
	Temperature float64 `json:"temperature"`
	Humidity    float64 `json:"humidity"`
	CreatedAt   string  `json:"created_at"`
}

func main() {
	jobs := make(chan SensorData, 100)

	for workerID := 1; workerID <= 3; workerID++ {
		go processSensorData(workerID, jobs)
	}

	http.HandleFunc("/sensor", receiveSensorData(jobs))

	log.Println("Go server is listening on http://localhost:8080")
	log.Fatal(http.ListenAndServe(":8080", nil))
}

func receiveSensorData(jobs chan<- SensorData) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		if r.Method != http.MethodPost {
			http.Error(w, "POST only", http.StatusMethodNotAllowed)
			return
		}

		var data SensorData
		err := json.NewDecoder(r.Body).Decode(&data)
		if err != nil {
			http.Error(w, "invalid JSON", http.StatusBadRequest)
			return
		}

		jobs <- data

		w.WriteHeader(http.StatusAccepted)
		_, _ = w.Write([]byte("queued\n"))
	}
}

func processSensorData(workerID int, jobs <-chan SensorData) {
	for data := range jobs {
		fmt.Printf(
			"worker=%d sensor=%d seq=%d temp=%.2f humidity=%.2f created_at=%s\n",
			workerID,
			data.SensorID,
			data.Sequence,
			data.Temperature,
			data.Humidity,
			data.CreatedAt,
		)

		time.Sleep(300 * time.Millisecond)
	}
}
