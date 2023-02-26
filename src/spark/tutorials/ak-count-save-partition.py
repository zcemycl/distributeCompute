from pyspark import SparkConf, SparkContext

conf = SparkConf().setAppName("Count Save and Partition RDD")
sc = SparkContext.getOrCreate(conf=conf)
rdd = sc.textFile("/opt/spark-data/quiz-2.txt")
print(rdd.collect())
rdd2 = rdd.flatMap(lambda x: x.split(" "))
print(rdd2.collect())
print(rdd2.count())
print(rdd2.countByValue())
print(rdd2.getNumPartitions()) # get n

rdd2.saveAsTextFile('/opt/spark-data/data-output/ak-out/') # save n partitions

rdd1only = rdd2.repartition(1)
rdd1only.saveAsTextFile('/opt/spark-data/data-output/ak-out1only/') # save 1 partition
readrdd2 = sc.textFile('/opt/spark-data/data-output/ak-out/') # read from directory instead of a file
print(readrdd2.collect())