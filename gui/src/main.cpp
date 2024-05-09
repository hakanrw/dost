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

static AdwNavigationPage* create_person_suggestion_page(const Person* person, int suggestion_mode) 
{
    GtkWidget *detailBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    ui::add_header_bar(detailBox);

    GtkWidget *scrolledWindow = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scrolledWindow, true);

    GtkWidget *list = ui::create_tall_vbox();

    gtk_box_append(GTK_BOX(list), ui::create_person_card(person));

    char subtitle[128];
    const char* mode;
    if (suggestion_mode == 1) mode = "Common Friends";
    if (suggestion_mode == 2) mode = "Similar Occupation";
    if (suggestion_mode == 3) mode = "Similar Age";
    
    sprintf(subtitle, "<b>Suggested Friends by %s</b>", mode);

    GtkWidget *suggestionsLabel = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(suggestionsLabel), subtitle);
    gtk_box_append(GTK_BOX(list), suggestionsLabel);

    std::vector<Person*> suggestions = graph.suggestFriends(person->getId(), suggestion_mode);

    for (std::vector<Person*>::const_iterator it = suggestions.begin(); it != suggestions.end(); ++it) {
        gtk_box_append(GTK_BOX(list), ui::create_person_card_small(*it));
    }

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolledWindow), list);
    gtk_box_append(GTK_BOX(detailBox), scrolledWindow);

    char title[128];
    sprintf(title, "Suggested Friends for %s", person->getName().c_str());

    AdwNavigationPage *detailPage = adw_navigation_page_new(detailBox, title);
    return detailPage;
}

static void suggestion_clicked(GtkWidget* widget __attribute__((unused)), GtkListBoxRow* row, gpointer data) {
    int person_id = GPOINTER_TO_INT(data);
    int suggestion_mode = gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(row)) + 1;

    adw_navigation_view_push(
        ADW_NAVIGATION_VIEW(navigationView), 
        create_person_suggestion_page(
            graph.getPerson(GPOINTER_TO_INT(person_id)), 
            suggestion_mode
        )
    );
}

static AdwNavigationPage* create_person_detail_page(const Person* person) 
{
    GtkWidget *detailBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    ui::add_header_bar(detailBox);

    GtkWidget *scrolledWindow = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scrolledWindow, true);

    GtkWidget *list = ui::create_tall_vbox();

    gtk_box_append(GTK_BOX(list), ui::create_person_card(person));

    // Friends

    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), "<b>Friends</b>");
    gtk_box_append(GTK_BOX(list), label);

    std::vector<int> friends = person->getFriends();

    for (std::vector<int>::const_iterator it = friends.begin(); it != friends.end(); ++it) {
        gtk_box_append(GTK_BOX(list), ui::create_person_card_small(graph.getPerson(*it)));
    }

    // Suggestions

    GtkWidget *suggestionsLabel = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(suggestionsLabel), "<b>Suggestions</b>");
    gtk_box_append(GTK_BOX(list), suggestionsLabel);

    GtkWidget *listBox = ui::create_suggestions_list_box();
    g_signal_connect(listBox, "row-activated", G_CALLBACK(suggestion_clicked), GINT_TO_POINTER(person->getId()));

    gtk_box_append(GTK_BOX(list), listBox);

    // Properties

    GtkWidget *propertiesLabel = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(propertiesLabel), "<b>Properties</b>");
    gtk_box_append(GTK_BOX(list), propertiesLabel);

    GtkWidget *propertiesBox = ui::create_properties_list_box(person);
    gtk_box_append(GTK_BOX(list), propertiesBox);

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolledWindow), list);
    gtk_box_append(GTK_BOX(detailBox), scrolledWindow);

    AdwNavigationPage *detailPage = adw_navigation_page_new(detailBox, person->getName().c_str());
    return detailPage;
}

static AdwNavigationPage* create_communities_page() 
{
    GtkWidget *communitiesBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    ui::add_header_bar(communitiesBox);

    GtkWidget *scrolledWindow = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scrolledWindow, true);

    GtkWidget *list = ui::create_tall_vbox();

    // Communities 

    std::vector<std::vector<int>> communities = graph.girvanNewman(4);

    for (size_t i = 0; i < communities.size(); i++) {
        GtkWidget *communityLabel = gtk_label_new(NULL);
        char title[32];
        sprintf(title, "<b>Community %d</b>", (int) (i + 1));
        gtk_label_set_markup(GTK_LABEL(communityLabel), title);
        gtk_box_append(GTK_BOX(list), communityLabel);

        for (size_t j = 0; j < communities[i].size(); j++) {
            gtk_box_append(GTK_BOX(list), ui::create_person_card_small(graph.getPerson(communities[i][j])));
        }
    }

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolledWindow), list);
    gtk_box_append(GTK_BOX(communitiesBox), scrolledWindow);

    AdwNavigationPage *communitiesPage = adw_navigation_page_new(communitiesBox, "Communities");
    return communitiesPage;
}

static void row_clicked(GtkButton* button __attribute__((unused)), gpointer id) 
{
    adw_navigation_view_push(ADW_NAVIGATION_VIEW(navigationView), create_person_detail_page(graph.getPerson(GPOINTER_TO_INT(id))));
}

static void detect_clicked(GtkButton* button __attribute__((unused))) 
{
    adw_navigation_view_push(ADW_NAVIGATION_VIEW(navigationView), create_communities_page());
}

static void add_list(GtkWidget *box) 
{
    GtkWidget *scrolledWindow = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scrolledWindow, true);

    GtkWidget *list = ui::create_tall_vbox();

    // Detect Communities

    GtkWidget *listBox = gtk_list_box_new();
    gtk_widget_add_css_class(listBox, "boxed-list");
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(listBox), GTK_SELECTION_NONE);

    GtkWidget *detectRow = adw_action_row_new();
    adw_preferences_row_set_title(ADW_PREFERENCES_ROW(detectRow), "Detect Communities");
    adw_action_row_add_suffix(ADW_ACTION_ROW(detectRow), gtk_image_new_from_icon_name("go-next-symbolic"));
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(detectRow), true);
    g_signal_connect(detectRow, "activated", G_CALLBACK(detect_clicked), NULL);

    gtk_list_box_append(GTK_LIST_BOX(listBox), detectRow);
    gtk_box_append(GTK_BOX(list), listBox);

    // People
    
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
