import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import argparse
import os
import sys

# Configurar el parser de argumentos
parser = argparse.ArgumentParser(description="Graficar tiempos promedio por tamaño de entrada.")
parser.add_argument("csv_path", help="Ruta al archivo CSV")
args = parser.parse_args()

# Verificar que el archivo existe
if not os.path.isfile(args.csv_path):
    print(f"Error: El archivo '{args.csv_path}' no existe.")
    sys.exit(1)

# Leer el CSV con manejo de errores
try:
    df = pd.read_csv(args.csv_path)
except Exception as e:
    print(f"Error al leer el archivo CSV: {e}")
    sys.exit(1)

# Verificar que las columnas necesarias existen
required_columns = {"test_name", "n", "time_ns"}
if not required_columns.issubset(df.columns):
    print(f"Error: El archivo debe contener las columnas: {', '.join(required_columns)}")
    sys.exit(1)

# Agrupar por test_name y n, calculando la media del tiempo
try:
    grouped = df.groupby(["test_name", "n"])["time_ns"].mean().reset_index()
except Exception as e:
    print(f"Error al procesar los datos: {e}")
    sys.exit(1)

# Crear el gráfico
try:
    sns.set_theme(style="whitegrid")
    plt.figure(figsize=(12, 6))

    sns.lineplot(data=grouped, x="n", y="time_ns", hue="test_name", marker='o')

    plt.title("Tiempo promedio por tamaño de entrada (n)")
    plt.xlabel("Tamaño de entrada (n)")
    plt.ylabel("Tiempo promedio (ns)")
    plt.legend(title="Método")
    plt.tight_layout()
    plt.show()
except Exception as e:
    print(f"Error al generar el gráfico: {e}")
    sys.exit(1)