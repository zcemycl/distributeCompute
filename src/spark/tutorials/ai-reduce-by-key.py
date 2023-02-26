from pyspark import SparkConf, SparkContext

conf = SparkConf().setAppName("Quiz Filter RDD")
sc = SparkContext.getOrCreate(conf=conf)
rdd = sc.textFile("/opt/spark-data/sample.txt")
print(rdd.collect())
rdd2 = rdd.flatMap(lambda x: x.split(" "))
print(rdd2.collect())
rdd3 = rdd2.map(lambda x: (x, 1))
print(rdd3.collect())
rdd4 = rdd3.reduceByKey(lambda x,y: x+y)
print(rdd4.collect())