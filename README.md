          C++ Client Simulator
          
 device-001 ─┐
 device-002 ─┤
 device-003 ─┤
     ...      ├──── HTTP/TCP ────> Go Server
 device-1000 ─┘                       │
                                     ├─ รับ Request
                                     ├─ Decode JSON
                                     ├─ Concurrency
                                     ├─ Queue / Channel
                                     ├─ Logs
                                     └─ Metrics

              Ubuntu / Linux
                    │
       ┌────────────┼────────────┐
       │            │            │
    Bash          Network      Services
   Scripts        Tools        systemd
       │
       └── Automation / Monitoring
