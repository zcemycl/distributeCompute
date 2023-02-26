from pyspark import SparkConf, SparkContext

def count_char(x):
    return [len(s) for s in x.split(" ")]

conf = SparkConf().setAppName("Quick for Create and Map RDD")
sc = SparkContext.getOrCreate(conf=conf)
rdd = sc.textFile("/opt/spark-data/quiz-1.txt")
print(rdd.collect())
rdd2 = rdd.map(count_char)
print(rdd2.collect())