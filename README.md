### Techniques
1. Spark
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
2. Python
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
2. OpenMPI
3. Ray
4. Cuda
5. C++ Parallelism
    - Thread Guard
    - Lock Guard
    - Race Condition
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