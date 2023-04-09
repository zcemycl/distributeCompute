```mermaid
gantt
    title Join exception
    dateFormat ss-SSS
    axisFormat %S-%L

    section t1
    available: 00-005, 00-015
    
    section main
    t1 init: 00-000, 0.005s
    exception: 00-005, 0.005s
    program: 00-000, 0.01s

    section sys
    thread error: 00-010, 0.005s
```