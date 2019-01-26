#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>
const static char program_name[] = "PassGen";
const static char generator_parameters[] = "Настройки генератора:";
const static char numbers[] = "Цифры";
const static char uppercase[] = "Прописные буквы";
const static char lowercase[] = "Строчные буквы";
const static char special[] = "Спец. символы !@#$%^&*()-_.,";
const static char length_0[] = "Длина пароля:";
const static char length_1[] = "- символов";
const static char generate[] = "Создать пароль";
const static char n_alphabet[] = "0123456789";
const static char u_alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const static char l_alphabet[] ="abcdefghijklmnopqrstuvwxyz";
const static char s_alphabet[] ="!@#$%^&*()-_.,";
GtkWidget* window,* vertical_container_0,* vertical_container_1,* horizontal_container,* parameters_frame,* cb_numbers,* cb_uppercase,* cb_lowercase,* cb_special,* length_label_0,* length_label_1,* spinner,* password_box,* generate_button;
GtkEntryBuffer* password_buffer;
bool main(unsigned char arguments_count, char* arguments_value[]);
void update_button_status(void);
void generate_password(void);
bool main(unsigned char arguments_count, char* arguments_value[])
{
  srand(time(0));
  password_buffer=gtk_entry_buffer_new (0, -1);
  gtk_init((int*)&arguments_count, &arguments_value);
  window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  vertical_container_0=gtk_vbox_new(0, 0);
  parameters_frame=gtk_frame_new(generator_parameters);
  vertical_container_1=gtk_vbox_new(0, 0);
  horizontal_container=gtk_hbox_new(0,0);
  cb_numbers = gtk_check_button_new_with_label(numbers);
  cb_uppercase = gtk_check_button_new_with_label(uppercase);
  cb_lowercase = gtk_check_button_new_with_label(lowercase);
  cb_special = gtk_check_button_new_with_label(special);
  length_label_0 = gtk_label_new(length_0);
  length_label_1 = gtk_label_new(length_1);
  spinner = gtk_spin_button_new_with_range(1, 64, 1);
  password_box = gtk_entry_new_with_buffer(password_buffer);
  generate_button = gtk_button_new_with_label(generate);
  gtk_window_set_title((GtkWindow*)window, program_name);
  gtk_widget_set_size_request((GtkWidget*)window, 244, 180);
  gtk_spin_button_set_value((GtkSpinButton*)spinner, 16);
  gtk_toggle_button_set_active((GtkToggleButton*)cb_numbers, 1);
  gtk_toggle_button_set_active((GtkToggleButton*)cb_uppercase, 1);
  gtk_toggle_button_set_active((GtkToggleButton*)cb_lowercase, 1);
  gtk_entry_set_editable ((GtkEntry*)password_box, 0);
  gtk_container_add((GtkContainer*)window, vertical_container_0);
  gtk_box_pack_start((GtkBox*)vertical_container_0, parameters_frame, 1, 1, 0);
  gtk_container_add((GtkContainer*)parameters_frame, vertical_container_1);
  gtk_box_pack_start((GtkBox*)vertical_container_1, cb_numbers, 0, 0, 0);
  gtk_box_pack_start((GtkBox*)vertical_container_1, cb_uppercase, 0, 0, 0);
  gtk_box_pack_start((GtkBox*)vertical_container_1, cb_lowercase, 0, 0, 0);
  gtk_box_pack_start((GtkBox*)vertical_container_1, cb_special, 0, 0, 0);
  gtk_box_pack_start((GtkBox*)vertical_container_1, horizontal_container, 0, 0, 0);
  gtk_box_pack_start((GtkBox*)horizontal_container, length_label_0, 0, 0, 4);
  gtk_box_pack_start((GtkBox*)horizontal_container, spinner, 0, 0, 0);
  gtk_box_pack_start((GtkBox*)horizontal_container, length_label_1, 0, 0, 4);
  gtk_box_pack_start((GtkBox*)vertical_container_0, password_box, 0, 0, 0);
  gtk_box_pack_start((GtkBox*)vertical_container_0, generate_button, 0, 0, 0);
  gtk_signal_connect((GtkObject*)window, "delete-event", (GtkSignalFunc)gtk_main_quit, 0);
  gtk_signal_connect((GtkObject*)cb_numbers, "toggled", (GtkSignalFunc)update_button_status, 0);
  gtk_signal_connect((GtkObject*)cb_uppercase, "toggled", (GtkSignalFunc)update_button_status, 0);
  gtk_signal_connect((GtkObject*)cb_lowercase, "toggled", (GtkSignalFunc)update_button_status, 0);
  gtk_signal_connect((GtkObject*)cb_special, "toggled", (GtkSignalFunc)update_button_status, 0);
  gtk_signal_connect((GtkObject*)generate_button, "clicked", (GtkSignalFunc)generate_password, 0);
  gtk_widget_show_all(window);
  gtk_main();
  exit(EXIT_SUCCESS);
  return 0;
}
void update_button_status(void)
{
  if(gtk_toggle_button_get_active((GtkToggleButton*)cb_numbers)||gtk_toggle_button_get_active((GtkToggleButton*)cb_uppercase)||gtk_toggle_button_get_active((GtkToggleButton*)cb_lowercase)||gtk_toggle_button_get_active((GtkToggleButton*)cb_special))
    {
      gtk_widget_set_sensitive(generate_button, 1);
    }
  else
    {
      gtk_widget_set_sensitive(generate_button, 0);
    }
  return;
}
void generate_password(void)
{
  char* alphabet,* password;
  uint8_t size, i;
  size = i=0;
  if(gtk_toggle_button_get_active((GtkToggleButton*)cb_numbers))
    {
      size+=sizeof(n_alphabet)-sizeof(char);
    }
  if(gtk_toggle_button_get_active((GtkToggleButton*)cb_uppercase))
    {
      size+=sizeof(u_alphabet)-sizeof(char);
    }
  if(gtk_toggle_button_get_active((GtkToggleButton*)cb_lowercase))
    {
      size+=sizeof(l_alphabet)-sizeof(char);
    }
  if(gtk_toggle_button_get_active((GtkToggleButton*)cb_special))
    {
      size+=sizeof(s_alphabet)-sizeof(char);
    }
  alphabet = malloc(size+sizeof(char));
  sprintf(alphabet, "");
  if(gtk_toggle_button_get_active((GtkToggleButton*)cb_numbers))
    {
      strcat(alphabet, n_alphabet);
    }
  if(gtk_toggle_button_get_active((GtkToggleButton*)cb_uppercase))
    {
      strcat(alphabet, u_alphabet);
    }
  if(gtk_toggle_button_get_active((GtkToggleButton*)cb_lowercase))
    {
      strcat(alphabet, l_alphabet);
    }
  if(gtk_toggle_button_get_active((GtkToggleButton*)cb_special))
    {
      strcat(alphabet, s_alphabet);
    }
  password = malloc(sizeof(char)*(gtk_spin_button_get_value((GtkSpinButton*)spinner)+1));
  for(i; i<gtk_spin_button_get_value((GtkSpinButton*)spinner);i++)
    {
      password[i]=alphabet[rand()%(size/sizeof(char))];
    }
  password[i]='\0';
  gtk_entry_buffer_set_text((GtkEntryBuffer*)password_buffer, password, -1);
  free(alphabet);
  free(password);
  return;
}
