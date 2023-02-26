from pyspark import SparkConf, SparkContext

conf = SparkConf().setAppName("Group By Key RDD")
sc = SparkContext.getOrCreate(conf=conf)
rdd = sc.textFile("/opt/spark-data/quiz-2.txt")
print(rdd.collect())
rdd2 = rdd.flatMap(lambda x: x.split(" "))
print(rdd2.collect())
rdd3 = rdd2.map(lambda x: (x, len(x)))
print(rdd3.collect())
rdd4 = rdd3.groupByKey().mapValues(list)
print(rdd4.collect())