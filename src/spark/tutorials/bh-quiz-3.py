from pyspark.sql import SparkSession
from pyspark.sql.functions import col, lit
from pyspark.sql.types import StructType, StructField, StringType, IntegerType

spark = SparkSession.builder.appName("Quiz Spark DataFrames 3").getOrCreate()
df = spark.read.options(
        header='True',
        inferSchema='True',
        delimiter=','
    )\
    .csv("/opt/spark-data/OfficeData.csv")
df.show()

df.sort(df.bonus).show()
df.sort(df.age.desc(), df.salary.asc()).show()
df.sort(df.age.desc(), df.bonus.desc(), df.salary.asc()).show()
