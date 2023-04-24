### Techniques
1. Python
    - Thread
        - IO Bound tasks
        - Context Switching
        - Race Condition
            ```mermaid
            gitGraph
                commit id: "main function"
                commit id: "init t1"
                branch thread1
                checkout thread1
                commit id: "load image 1"
                checkout main
                commit id: "init t2"
                checkout main
                branch thread2
                commit id: "load image 2"
                checkout main
                merge thread1 id: "gil 1"
                merge thread2 id: "gil 2"
            ```
    - Multiprocessing
        - CPU Bound tasks
        - May cause overhead
    - Concurrent.futures
        - Combine Threading and Multiprocessing Libraries
    - Asyncio
        - IO Bound tasks
        - Similar to Threading, but one thread one process
            ```mermaid
            gitGraph
                commit id: "main function"
                commit id: "async call 1"
                commit id: "async call 2"
                commit id: "await" type: HIGHLIGHT
                commit id: "complete"
            ```
    - Spark
        ```
        git clone https://github.com/zcemycl/systemDeploy.git
        cd systemDeploy/src/containers/docker/spark/
        docker build -t cluster-apache-spark:latest .
        docker-compose up -d
        mkdir /tmp/data
        mkdir /tmp/apps
        cp *.csv /tmp/data
        cp *.py /tmp/apps
        mkdir /tmp/data/data-output
        docker exec -it spark-spark-master-1 bash -c "bin/spark-submit /opt/spark-apps/test.py"
        ```
        ```mermaid
        flowchart LR;
            A[main] --> B[master node];
            B --> C[worker node 1] & D[worker node 2]
        ```
    - Ray

2. Cuda (Compute Unified Device Architecture)
    - CPU: Latency device with high local speed, small no. of cores, have optimisation hardware. 
    - GPU: Through put device with low lock speed, thousand of cores, no optimisation hardware. Context switching done by hardware, thread schedulers and dispatch units are implemented in hardware. 
        ```mermaid
        gitGraph
            commit id: "init resources"
            branch cpu
            commit id: "init data"
            branch gpu
            commit id: "transfer data"
            commit id: "kernel launch (grid/block)"
            checkout cpu
            merge gpu id: "transfer result"
            checkout main
            merge cpu id: "reclaim memory"
        ```
3. C++ Parallelism
    - Thread Guard, Lock Guard, Race Condition, Deadlock, Unique Lock, Async Future, Promise
    - JThread, Stop Token (Macos clang does not support, Alternative is run with dockerfile), Coroutines
    - Boost (Dockerfile)
    - OpenMP
    - OpenMPI
    - Join vs Detach
        ```mermaid
        gantt 
            title Bar 2000 Detach, Foo 1000 Join
            dateFormat ss-SSS
            axisFormat %S-%L
            section t1 detach
            "print bar 1": 00-000, 0.005s
            sleep: 00-005, 2s
            "print bar 2": 02-005, 0.005s

            section t2 join
            "print bar 1": 00-005, 0.005s
            sleep: 00-010, 1s
            "print bar 2": 01-010, 0.005s

            section stdout
            1. bar: 00-000, 0.005s
            2. foo: 00-005, 0.005s
            bar: crit,  02-005, 0.005s
            3. foo: 01-010, 0.005s

            section main
            program: a10, 00-000, 1.015s
        ```
    - Locks
        ```mermaid
        gantt
            title Double locks
            dateFormat ss-SSS
            axisFormat %S-%L
            section t1
            m1 lock: 00-000, 0.005s
            t1m1: 00-005, 0.005s
            sleep: 00-010, 1s
            wait m2 unlock: crit, 01-010, 0.51s
            m2 lock: 01-520, 0.005s
            t1m2: 01-525, 0.005s
            m1 m2 unlock: 01-530, 0.005s


            section t2
            m2 lock: 00-005, 0.005s
            t2m2: 00-010, 0.005s
            sleep: 00-015, 1.5s
            m2 unlock: 01-515, 0.005s

            section stdout
            1. t1m1: 00-005, 0.005s
            2. t2m2: 00-010, 0.005s
            3. t1m2: 01-525, 0.005s
        ```
    - Racing Conditions
        ```mermaid
        gantt 
            title Racing Condition
            dateFormat ss-SSS
            axisFormat %S-%L

            section Thread 1
            op1: 00-000, 0.002s
            op2: 00-002, 0.002s
            op3: 00-004, 0.002s

            section Thread 2
            op1: 00-001, 0.002s
            op2: 00-003, 0.002s
            op3: 00-005, 0.002s

            section Linked List
            [4][1,2,3],s-1: 00-000, 0.002s
            [5][1,2,3],s-1: 00-001, 0.002s
            [4,1,2,3],s-1: 00-002, 0.002s
            [5,1,2,3],s-1: 00-003, 0.002s
            [4,1,2,3],s-4: 00-004, 0.002s
            [5,1,2,3],s-5: 00-005, 0.002s

            section expected
            [5,4,1,2,3],s-5: 00-000, 0.007s

            section final
            [5,1,2,3],s-5: 00-000, 0.007s
        ```

### References
1. [Distributed, parallel, concurrent, High-Performance Computing.pdf](https://esling.github.io/documents/Generic.6b.Concurrence.pdf)
2. [Compiler support for C++20](https://en.cppreference.com/w/cpp/compiler_support/20#C.2B.2B14_library_features)