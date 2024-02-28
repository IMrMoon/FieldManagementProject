//
// Created by sgvch on 26/02/2024.
//
#define RESET 7
#define CYAN 9
#include <windows.h>
#include "Menu.h"

enum manager_Or_player {manager = 1 , player};
enum reg_or_login {reg = 1, login};
enum player_options {schedule_game_player = 1, cancel_game, search_field_by_type, search_field_by_city, edit_details_player, view_future_games, view_games_history, rate_a_field, quit1};
enum manager_options {add_field = 1, delete_field, edit_details_manager, view_future_games_by_date, view_future_games_by_field, make_unavailable_dates, view_rate_manager, quit2};


void first_menu(){ //menu for choose if he is a manager or player.
    int option = 0;
    do {
        set_text_color(CYAN);
        cout << "+--------------------------------------+" << endl;
        cout << "| " << "Hello and welcome to the Field management system!" << " |" << endl;
        cout << "| " << "Please choose if you are a Manager/Player:    " << " |" << endl;
        cout << "| " << "1) Manager                                     " << " |" << endl;
        cout << "| " << "2) Player                                      " << " |" << endl;
        cout << "+--------------------------------------+" << endl;
        set_text_color(RESET);

        cin >> option;
        system("CLS");
        switch (option) {
            case (manager): {
                manager_reg_or_login_menu();
                break;
            }
            case (player): {
                player_reg_or_login_menu();
                break;
            }
            default: {
                set_text_color(31);
                cout << "Illegal option, Please retry." << endl;
                set_text_color(RESET);
                option = 0;
                break;
            }
        }
    } while (option == 0);
}

void player_reg_or_login_menu(){
    int option = 0;
    string player_id;
    do {
        set_text_color(CYAN);
        cout << "+--------------------------------------+" << endl;
        cout << "| " << "Hello and welcome to the Field management system!" << " |" << endl;
        cout << "| " << "Please choose Register/Login:    " << " |" << endl;
        cout << "| " << "1) Register                                     " << " |" << endl;
        cout << "| " << "2) Login                                      " << " |" << endl;
        cout << "+--------------------------------------+" << endl;
        set_text_color(RESET);
        cin.ignore();
        cin >> option;
        system("CLS");
        switch (option) {
            case (reg): {
                player_id = player_register();
                cout << "Registered successfully" << endl;
                player_menu(player_id);
                break;
            }
            case (login): {
                player_id = player_login(); //add forget pass option
                player_menu(player_id);
                break;
            }
            default: {
                set_text_color(31);
                cout << "Illegal option, Please retry." << endl;
                set_text_color(RESET);
                option = 0;
                break;
            }
        }
    } while (option == 0);
}

void manager_reg_or_login_menu(){
    int option = 0;
    string manager_id;
    do {
        cout << "+--------------------------------------+" << endl;
        cout << "| " << "Hello and welcome to the Field management system!" << " |" << endl;
        cout << "| " << "Please choose Register/Login:    " << " |" << endl;
        cout << "| " << "1) Register                                     " << " |" << endl;
        cout << "| " << "2) Login                                      " << " |" << endl;
        cout << "+--------------------------------------+"  << endl;

        cin >> option;
        system("CLS");
        switch (option) {
            case (reg): {
                manager_id = manager_register();
                manager_menu(manager_id);
                break;
            }
            case (login): {
                manager_id = manager_login(); //add forget pass option
                manager_menu(manager_id);
                break;
            }
            default: {
                set_text_color(31);
                cout << "Illegal option, Please retry." << endl;
                set_text_color(RESET);
                option = 0;
                break;
            }
        }
    } while (option == 0);
}

void player_menu(string& player_id){
    int option = 0;
    do {
        set_text_color(CYAN);
        cout << "+--------------------------------------+" << endl;
        cout << "| " << "Hello and welcome to the Field management system!" << " |" << endl;
        cout << "| " << "Please choose Register/Login:    " << " |" << endl;
        cout << "| " << "1) Schedule game                                     " << " |" << endl;
        cout << "| " << "2) Cancel Game                                      " << " |" << endl;
        cout << "| " << "3) Search Field by type                                      " << " |" << endl;
        cout << "| " << "4) Search Field by city                                      " << " |" << endl;
        cout << "| " << "5) Edit details                                      " << " |" << endl;
        cout << "| " << "6) View future games                                      " << " |" << endl;
        cout << "| " << "7) View games history                                      " << " |" << endl;
        cout << "| " << "8) Rate a field                                     " << " |" << endl;
        cout << "| " << "9) Quit                                    " << " |" << endl;
        cout << "+--------------------------------------+" << endl;
        set_text_color(RESET);

        cin >> option;
        system("CLS");
        switch (option) {
            case (schedule_game_player): {
                //schedule_game();

                break;
            }
            case (cancel_game): {
                //delete_game_order(); //need to write and fix

                break;
            }
            case (search_field_by_type): {
                //view_fields_by_fieldType();

                break;
            }
            case (search_field_by_city): {
                //view_fields_by_city();

                break;
            }
            case (edit_details_player): {
                //edit_player_details();

                break;
            }
            case (view_future_games): {
                //view_player_games();

                break;
            }
            case (view_games_history): {
                //view_previous_games();

                break;
            }
            case (rate_a_field): {
                //addRate(); //need to change

                break;
            }
            case (quit1): {
                set_text_color(31);
                cout << "Exiting the menu!" << endl;
                set_text_color(RESET);
                break;
            }
            default: {
                set_text_color(31);
                cout << "Illegal option, Please retry." << endl;
                set_text_color(RESET);
                option = 0;
                break;
            }
        }
    } while (option != 9);
}
void manager_menu(string& manager_id){
    int option = 0;
    do {
        set_text_color(CYAN);
        cout << "+--------------------------------------+" << endl;
        cout << "| " << "Hello and welcome to the Field management system!" << " |" << endl;
        cout << "| " << "Please choose Register/Login:    " << " |" << endl;
        cout << "| " << "1) Add Field                                     " << " |" << endl;
        cout << "| " << "2) Delete Field                                      " << " |" << endl;
        cout << "| " << "3) Edit details                                      " << " |" << endl;
        cout << "| " << "4) View future games by date                                      " << " |" << endl;
        cout << "| " << "5) View future games by field                                      " << " |" << endl;
        cout << "| " << "6) Make unavailable dates                                      " << " |" << endl;
        cout << "| " << "7) View Rate                                      " << " |" << endl;
        cout << "| " << "8) Quit                                     " << " |" << endl;
        cout << "+--------------------------------------+" << endl;
        set_text_color(RESET);

        cin >> option;
        system("CLS");
        switch (option) {
            case (add_field): {
                //addField();

                break;
            }
            case (delete_field): {
                //deleteField();

                break;
            }
            case (edit_details_manager): {
                //edit_manager_details();

                break;
            }
            case (view_future_games_by_date): {
                view_orders_by_date(manager_id);

                break;
            }
            case (view_future_games_by_field): {
                view_field_orders(manager_id);

                //view_field_orders();
                break;
            }
            case (make_unavailable_dates): {
//                string field_id = get_field_id(manager_id);
//                mark_dates_as_unavailable(manager_id,field_id,);
                break;
            }
            case (view_rate_manager): {
                //view_rate();

                break;
            }
            case (quit2): {
                set_text_color(31);
                cout << "Exiting the menu!" << endl;
                set_text_color(RESET);
                break;
            }
            default: {
                set_text_color(31);
                cout << "Illegal option, Please retry." << endl;
                set_text_color(RESET);
                option = 0;
                break;
            }
        }
    } while (option != 8);
}

void set_text_color(int color) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
