from pyspark.sql import SparkSession
from pyspark.sql.functions import col, lit, sum, avg, max, min, mean, count
from pyspark.sql.types import StructType, StructField, StringType, IntegerType

spark = SparkSession.builder.appName("Quiz Spark DataFrames 4").getOrCreate()
df = spark.read.options(
        header='True',
        inferSchema='True',
        delimiter=','
    )\
    .csv("/opt/spark-data/StudentData.csv")

df.groupBy('course').count().show()
df.groupBy('course','gender').count().show()
df.groupBy('course','gender').sum('marks').show()
df.groupBy('course','age').agg(min('marks'),max('marks'),avg('marks')).show()

df = spark.read.csv('/opt/spark-data/WordData.txt')
df.show()
df.groupBy('_c0').count().show()