from pyspark.sql import SparkSession
from pyspark.sql.functions import col, lit
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

spark = SparkSession.builder.appName("Filter Row Spark DataFrames").getOrCreate()
df = spark.read.options(
        header='True',
        inferSchema='True',
        delimiter=','
    )\
    .schema(schema)\
    .csv("/opt/spark-data/StudentData.csv")

df = df.withColumn("total marks", lit(120))\
        .withColumn("average marks", col("marks")/col("total marks")*100)
df.show()

dfgreater80 = df.filter((col("average marks")>80) & (df.course == "OOP"))
dfgreater80.show()

dfgreater60 = df.filter((col("average marks")>60) & (df.course == "Cloud"))
dfgreater60.show()