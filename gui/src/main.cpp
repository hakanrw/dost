#include <adwaita.h>
#include <cstdlib>
#include <vector>

#include <Person.h>
#include <utils.h>

Graph graph;

static void add_header_bar(GtkWidget *box) {

    GtkWidget *headerBar = adw_header_bar_new();
    gtk_box_append(GTK_BOX(box), headerBar);
}

static GtkWidget* create_person_row(Person* person) {
    GtkWidget *row = gtk_list_box_row_new();
    // gtk_widget_set_size_request(row, 0, 50);
    gtk_widget_add_css_class(row, "card");


    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_set_margin_top(vbox, 12);
    gtk_widget_set_margin_bottom(vbox, 12);
    gtk_widget_set_margin_start(vbox, 8);
    gtk_widget_set_margin_end(vbox, 8);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    GtkWidget *avatar = adw_avatar_new(40, person->getName().c_str(), true);
    GtkWidget *label = gtk_label_new(person->getName().c_str());

    gtk_box_append(GTK_BOX(hbox), avatar);
    gtk_box_append(GTK_BOX(hbox), label);
    gtk_box_append(GTK_BOX(vbox), hbox);

    gtk_box_append(GTK_BOX(vbox), gtk_separator_new(GTK_ORIENTATION_HORIZONTAL));
    
    char str[24];
    sprintf(str, "%d, %s", person->getAge(), person->getGender().c_str());

    GtkWidget *genderBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(genderBox), gtk_image_new_from_icon_name("user-info-symbolic"));
    gtk_box_append(GTK_BOX(genderBox), gtk_label_new(str));

    gtk_box_append(GTK_BOX(vbox), genderBox);

    GtkWidget *occupationBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(occupationBox), gtk_image_new_from_icon_name("preferences-system-symbolic"));
    gtk_box_append(GTK_BOX(occupationBox), gtk_label_new(person->getOccupation().c_str()));

    gtk_box_append(GTK_BOX(vbox), occupationBox);

    gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(row), vbox);
    return row;
}

static void add_list(GtkWidget *box) {
    GtkWidget *scrolledWindow = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scrolledWindow, true);

    GtkWidget *list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_set_margin_top(list, 20);
    gtk_widget_set_margin_bottom(list, 20);
    gtk_widget_set_hexpand(list, false);
    gtk_widget_set_halign(list, GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(list, 400, 0);
    
    std::vector<std::pair<int, Person>> _graph = graph.getGraph();
    
    for (std::vector<std::pair<int, Person>>::const_iterator it = _graph.begin(); it != _graph.end(); ++it) {
        gtk_box_append(GTK_BOX(list), create_person_row((Person*)&it->second));
    }

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolledWindow), list);
    gtk_box_append(GTK_BOX(box), scrolledWindow);
}

static void
activate_cb(GtkApplication *app)
{
    GtkWidget *window = adw_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(window), "Dost");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);
    gtk_window_present(GTK_WINDOW(window));

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    add_header_bar(box);
    add_list(box);

    adw_application_window_set_content(ADW_APPLICATION_WINDOW(window), box);
}

int main(int argc,
         char *argv[])
{
    graph = readData("social_network.csv");

    g_autoptr(AdwApplication) app = NULL;

    app = adw_application_new("dev.candar.project.Dost", G_APPLICATION_FLAGS_NONE);

    g_signal_connect(app, "activate", G_CALLBACK(activate_cb), NULL);

    return g_application_run(G_APPLICATION(app), argc, argv);
}
