from pyspark import SparkConf, SparkContext

conf = SparkConf().setAppName("Quiz Filter RDD")
sc = SparkContext.getOrCreate(conf=conf)
rdd = sc.textFile("/opt/spark-data/quiz-2.txt")
print(rdd.collect())
rdd2 = rdd.flatMap(lambda x: x.split(" "))
print(rdd2.collect())
rdd3 = rdd2.filter(lambda x: x[0]!='a' and x[0]!='c')
print(rdd3.collect())