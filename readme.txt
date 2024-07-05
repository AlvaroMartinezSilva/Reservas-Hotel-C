Aquí tienes un ejemplo de cómo redactar un archivo README que explique tu proyecto de sistema de reservas para un hotel en C. Este documento proporciona una descripción general del proyecto, cómo funciona, y cómo compilar y ejecutar el programa.

---

# Hotel Reservation System

## Descripción General
El sistema de reservas de hotel es una aplicación de consola desarrollada en C que permite a los usuarios gestionar reservaciones en un hotel ficticio. La aplicación admite la adición y cancelación de reservas, generación de informes de ocupación y de ingresos, y mantiene los datos persistentes a través de sesiones mediante la carga y guardado de datos en un archivo.

## Características
- **Agregar Reservas**: Permite a los usuarios reservar una de los tres tipos de habitaciones disponibles (Simple, Doble, Suite) según la disponibilidad y las fechas deseadas.
- **Cancelar Reservas**: Los usuarios pueden cancelar reservas existentes proporcionando el nombre del cliente.
- **Generar Informes**: Produce un informe que muestra el número de días ocupados para cada tipo de habitación y los ingresos totales generados.
- **Persistencia de Datos**: Guarda automáticamente las reservas en un archivo y las carga al iniciar el programa para mantener el estado entre sesiones.

## Estructuras de Datos
El sistema utiliza las siguientes estructuras principales:
- `Room`: Representa una habitación individual en el hotel, incluyendo su número, tipo, ocupación por día, precio por noche, y el nombre del ocupante.
- `RoomType`: Enumeración que define los tipos de habitaciones disponibles.

## Compilación y Ejecución
Para compilar y ejecutar el sistema de reservas, necesitarás un compilador de C que soporte C99 o superior, como GCC. Puedes compilar el programa usando el siguiente comando:

```bash
gcc -o hotel_reservation_system main.c
```

Para ejecutar el programa, simplemente utiliza:

```bash
./hotel_reservation_system
```

## Uso
Al ejecutar el programa, se presenta al usuario un menú de opciones que incluye agregar reserva, cancelar reserva, generar informe y salir. El usuario puede seleccionar una opción ingresando el número correspondiente.

### Ejemplo de Uso del Menú
```
Hotel Reservation System
1. Add Reservation
2. Cancel Reservation
3. Generate Report
4. Exit
Enter your choice: 
```

## Notas de Desarrollo
- El archivo de datos `hotel_data.dat` se crea y utiliza para almacenar el estado del hotel entre ejecuciones. Asegúrate de no eliminar este archivo si deseas mantener los datos persistentes.

## Limitaciones
- El sistema asume que el año tiene 365 días sin manejar años bisiestos.
- Las entradas del usuario deben ser validadas cuidadosamente para evitar errores en la ejecución.
