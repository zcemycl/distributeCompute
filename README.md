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
2. OpenMPI
3. Ray
4. Cuda
5. C++ Parallelism
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