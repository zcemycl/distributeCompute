from pyspark.sql import SparkSession
from pyspark.sql.functions import col, lit, sum, avg, max, min, mean, count
from pyspark.sql.types import StructType, StructField, StringType, IntegerType

# direct from csv to df
schema = StructType([
    StructField("age", IntegerType(), True),
    StructField("gender", StringType(), True),
    StructField("name", StringType(), True),
    StructField("course", StringType(), True),
    StructField("roll", StringType(), True),
    StructField("marks", IntegerType(), True),
    StructField("email", StringType(), True),
])

spark = SparkSession.builder.appName("GroupBy Spark DataFrames").getOrCreate()
df = spark.read.options(
        header='True',
        inferSchema='True',
        delimiter=','
    )\
    .schema(schema)\
    .csv("/opt/spark-data/StudentData.csv")

df.groupBy("gender").sum("marks").show()
df.groupBy("course").count().show()
df.groupBy("gender", "course").max("marks").show()
df.groupBy("gender", "course").agg(
    count("*").alias("Total enrollments"), 
    sum("marks"), 
    min("marks"),
    max("marks"),
).show()