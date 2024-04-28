#pragma once

#include <adwaita.h>
#include <gtk/gtk.h>
#include <Person.h>
#include <globals.h>

namespace ui {
    GtkWidget* create_person_card(const Person* person);
    GtkWidget* create_person_card_small(const Person* person);

    GtkWidget* create_suggestions_list_box(const Person* person);
    
    GtkWidget* create_tall_vbox();
    
    void add_header_bar(GtkWidget *box);
}