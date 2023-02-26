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

spark = SparkSession.builder.appName("Select WithCols Alias Spark DataFrames").getOrCreate()
df = spark.read.options(
        header='True',
        inferSchema='True',
        delimiter=','
    )\
    .schema(schema)\
    .csv("/opt/spark-data/StudentData.csv")

df.select("name", "gender").show()
df.select(df.name, df.email).show()
df.select(col("roll"), col("name")).show()
df.select("*").show()
df.select(df.columns[2]).show()

# cast function to a specific column, assign back to a specific column
df2 = df.withColumn("roll", col("roll").cast("String"))
df2.printSchema()
df2 = df2.withColumn("new marks", col("marks")+19)
df2 = df2.withColumn("Country", lit("USA"))
df2.show()

df2 = df2.withColumnRenamed("gender", "sex")
df2.show()

df2.select(col("Country").alias("country")).show()