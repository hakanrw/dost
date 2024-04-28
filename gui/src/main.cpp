#include <adwaita.h>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <Person.h>
#include <ui.h>
#include <utils.h>
#include <globals.h>

Graph graph;
GtkWidget *navigationView;

static AdwNavigationPage* create_person_detail_page(const Person* person) 
{
    GtkWidget *detailBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    ui::add_header_bar(detailBox);

    GtkWidget *scrolledWindow = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scrolledWindow, true);

    GtkWidget *list = ui::create_tall_vbox();

    gtk_box_append(GTK_BOX(list), ui::create_person_card(person));

    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), "<b>Friends</b>");
    gtk_box_append(GTK_BOX(list), label);

    std::vector<int> friends = person->getFriends();

    for (std::vector<int>::const_iterator it = friends.begin(); it != friends.end(); ++it) {
        gtk_box_append(GTK_BOX(list), ui::create_person_card_small(graph.getPerson(*it)));
    }

    GtkWidget *suggestionsLabel = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(suggestionsLabel), "<b>Suggestions</b>");
    gtk_box_append(GTK_BOX(list), suggestionsLabel);

    GtkWidget *listBox = ui::create_suggestions_list_box(person);

    gtk_box_append(GTK_BOX(list), listBox);

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolledWindow), list);
    gtk_box_append(GTK_BOX(detailBox), scrolledWindow);

    AdwNavigationPage *detailPage = adw_navigation_page_new(detailBox, person->getName().c_str());
    return detailPage;
}

static void row_clicked(GtkButton* button, gpointer id) 
{
    adw_navigation_view_push(ADW_NAVIGATION_VIEW(navigationView), create_person_detail_page(graph.getPerson(GPOINTER_TO_INT(id))));
}

static void add_list(GtkWidget *box) 
{
    GtkWidget *scrolledWindow = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scrolledWindow, true);

    GtkWidget *list = ui::create_tall_vbox();
    
    std::vector<std::pair<int, Person>> _graph = graph.getGraph();
    
    for (std::vector<std::pair<int, Person>>::const_iterator it = _graph.begin(); it != _graph.end(); ++it) {
        GtkWidget* row = ui::create_person_card((Person*)&it->second);
        g_signal_connect(row, "clicked", G_CALLBACK(row_clicked), GINT_TO_POINTER(it->second.getId()));
        gtk_box_append(GTK_BOX(list), row);
    }

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolledWindow), list);
    gtk_box_append(GTK_BOX(box), scrolledWindow);
}

static void activate_cb(GtkApplication *app)
{
    GtkWidget *window = adw_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(window), "Dost");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 900);
    gtk_window_present(GTK_WINDOW(window));

    navigationView = adw_navigation_view_new();

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    ui::add_header_bar(box);
    add_list(box);

    AdwNavigationPage *homePage = adw_navigation_page_new_with_tag(box, "Dost", "home");
    adw_navigation_view_add(ADW_NAVIGATION_VIEW(navigationView), homePage);
    
    GtkWidget *detailBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    ui::add_header_bar(detailBox);

    AdwNavigationPage *detailPage = adw_navigation_page_new_with_tag(detailBox, "Details", "detail");
    adw_navigation_view_add(ADW_NAVIGATION_VIEW(navigationView), detailPage);

    adw_application_window_set_content(ADW_APPLICATION_WINDOW(window), navigationView);
}

int main(int argc, char *argv[])
{
    graph = readData("social_network.csv");

    g_autoptr(AdwApplication) app = NULL;

    app = adw_application_new("dev.candar.project.Dost", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(activate_cb), NULL);

    return g_application_run(G_APPLICATION(app), argc, argv);
}
