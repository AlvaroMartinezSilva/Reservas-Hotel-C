#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_ROOM_TYPES 3
#define MAX_NAME_LEN 50
#define MAX_DAYS 365
#define MAX_ROOMS 50


typedef enum {
    SINGLE, DOUBLE, SUITE
} RoomType;

const char* room_type_names[] = {"Single", "Double", "Suite"};
const float base_prices[MAX_ROOM_TYPES] = {100.0, 180.0, 250.0};

typedef struct {
    int room_number;
    RoomType type;
    int is_occupied[MAX_DAYS];
    float price_per_night;
    char occupant_name[MAX_NAME_LEN];
} Room;

Room hotel_rooms[MAX_ROOMS];


void initialize_rooms() {
    for (int i = 0; i < MAX_ROOMS; i++) {
        hotel_rooms[i].room_number = i + 1;
        hotel_rooms[i].type = i % MAX_ROOM_TYPES; // Distribuir los tipos de habitaciones
        hotel_rooms[i].price_per_night = base_prices[hotel_rooms[i].type];
        memset(hotel_rooms[i].is_occupied, 0, sizeof(hotel_rooms[i].is_occupied));
    }
}
void save_to_file() {
    FILE *file = fopen("hotel_data.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(hotel_rooms, sizeof(Room), MAX_ROOMS, file);
    fclose(file);
    printf("Hotel data saved successfully.\n");
}

void load_from_file() {
    FILE *file = fopen("hotel_data.dat", "rb");
    if (file == NULL) {
        printf("No saved data found, initializing new hotel data.\n");
        initialize_rooms();
        return;
    }
    fread(hotel_rooms, sizeof(Room), MAX_ROOMS, file);
    fclose(file);
    printf("Hotel data loaded successfully.\n");
}

int add_reservation(char *name, int start_day, int end_day, RoomType type) {
    if (!is_valid_name(name) || !is_valid_date(start_day, end_day)) {
        printf("Invalid input data.\n");
        return -1;
    }

    for (int i = 0; i < MAX_ROOMS; i++) {
        if (hotel_rooms[i].type == type) {
            int available = 1;
            for (int j = start_day; j <= end_day; j++) {
                if (hotel_rooms[i].is_occupied[j]) {
                    available = 0;
                    break;
                }
            }
            if (available) {
                for (int j = start_day; j <= end_day; j++) {
                    hotel_rooms[i].is_occupied[j] = 1;
                }
                strcpy(hotel_rooms[i].occupant_name, name);
                printf("Reservation added for %s in %s room %d.\n", name, room_type_names[type], hotel_rooms[i].room_number);
                return hotel_rooms[i].room_number;
            }
        }
    }
    printf("No available %s rooms for the selected dates.\n", room_type_names[type]);
    return -1;
}
void generate_report() {
    int occupied_count[MAX_ROOM_TYPES] = {0};
    float total_income = 0.0;

    for (int i = 0; i < MAX_ROOMS; i++) {
        for (int j = 1; j <= MAX_DAYS; j++) {
            if (hotel_rooms[i].is_occupied[j]) {
                occupied_count[hotel_rooms[i].type]++;
                total_income += hotel_rooms[i].price_per_night;
            }
        }
    }

    for (int i = 0; i < MAX_ROOM_TYPES; i++) {
        printf("%s rooms occupied: %d days\n", room_type_names[i], occupied_count[i]);
    }
    printf("Total income: $%.2f\n", total_income);
}
int main() {
    load_from_file(); // Cargar los datos al iniciar el programa
    char guest_name[MAX_NAME_LEN];
    int start, end, choice, room_type;

    while (1) {
        printf("\nHotel Reservation System\n");
        printf("1. Add Reservation\n");
        printf("2. Cancel Reservation\n");
        printf("3. Generate Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        getchar(); // consume the newline character after the integer input

        switch (choice) {
        case 1:
            printf("Enter guest name: ");
            fgets(guest_name, MAX_NAME_LEN, stdin);
            guest_name[strcspn(guest_name, "\n")] = 0; // Remove newline character
            printf("Enter start day (1-365): ");
            scanf("%d", &start);
            printf("Enter end day (1-365): ");
            scanf("%d", &end);
            printf("Select room type (0-Single, 1-Double, 2-Suite): ");
            scanf("%d", &room_type);
            if (add_reservation(guest_name, start, end, room_type) != -1) {
                save_to_file(); // Guardar cambios tras una reserva exitosa
            }
            break;
        case 2:
            printf("Enter guest name to cancel: ");
            fgets(guest_name, MAX_NAME_LEN, stdin);
            guest_name[strcspn(guest_name, "\n")] = 0;
            if (cancel_reservation(guest_name) != -1) {
                save_to_file(); // Guardar cambios tras una cancelación exitosa
            }
            break;
        case 3:
            generate_report();
            break;
        case 4:
            printf("Exiting system.\n");
            return 0;
        default:
            printf("Invalid choice. Please choose again.\n");
        }
    }
    return 0;
}
