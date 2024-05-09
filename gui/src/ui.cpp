#include <ui.h>

#include <iostream>

GtkWidget* ui::create_person_card(const Person* person) {
    GtkWidget *row = gtk_button_new();
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

    GtkWidget *friendsBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(friendsBox), gtk_image_new_from_icon_name("system-users-symbolic"));

    std::vector<int> friends = person->getFriends();

    for (std::vector<int>::const_iterator it = friends.begin(); it != friends.end(); ++it) {
        GtkWidget *avatar = adw_avatar_new(15, graph.getPerson(*it)->getName().c_str(), true);
        if (it == friends.begin()) gtk_widget_set_margin_start(avatar, 5);
        gtk_box_append(GTK_BOX(friendsBox), avatar);
    }
    //gtk_box_append(GTK_BOX(occupationBox), gtk_label_new(person->getOccupation().c_str()));

    gtk_box_append(GTK_BOX(vbox), friendsBox);

    gtk_button_set_child(GTK_BUTTON(row), vbox);

    return row;
}

GtkWidget* ui::create_person_card_small(const Person* person) {
    GtkWidget *row = gtk_button_new();
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
    
    GtkWidget *bottomBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);

    char str[24];
    sprintf(str, "%d, %s", person->getAge(), person->getGender().c_str());

    GtkWidget *genderBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_size_request(genderBox, 100, 0);
    gtk_box_append(GTK_BOX(genderBox), gtk_image_new_from_icon_name("user-info-symbolic"));
    gtk_box_append(GTK_BOX(genderBox), gtk_label_new(str));

    gtk_box_append(GTK_BOX(bottomBox), genderBox);

    GtkWidget *occupationBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(occupationBox), gtk_image_new_from_icon_name("preferences-system-symbolic"));
    gtk_box_append(GTK_BOX(occupationBox), gtk_label_new(person->getOccupation().c_str()));

    gtk_box_append(GTK_BOX(bottomBox), occupationBox);

    // GtkWidget *friendsBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    // gtk_box_append(GTK_BOX(friendsBox), gtk_image_new_from_icon_name("system-users-symbolic"));

    // std::vector<int> friends = person->getFriends();

    // for (std::vector<int>::const_iterator it = friends.begin(); it != friends.end(); ++it) {
    //     GtkWidget *avatar = adw_avatar_new(15, graph.getPerson(*it)->getName().c_str(), true);
    //     if (it == friends.begin()) gtk_widget_set_margin_start(avatar, 5);
    //     gtk_box_append(GTK_BOX(friendsBox), avatar);
    // }
    // //gtk_box_append(GTK_BOX(occupationBox), gtk_label_new(person->getOccupation().c_str()));

    // gtk_box_append(GTK_BOX(bottomBox), friendsBox);

    gtk_box_append(GTK_BOX(vbox), bottomBox);

    gtk_button_set_child(GTK_BUTTON(row), vbox);

    return row;
}

GtkWidget* ui::create_tall_vbox() {
    GtkWidget *list = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_set_margin_top(list, 20);
    gtk_widget_set_margin_bottom(list, 20);
    gtk_widget_set_hexpand(list, false);
    gtk_widget_set_halign(list, GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(list, 400, 0);

    return list;
}

GtkWidget* ui::create_suggestions_list_box() {

    GtkWidget *listBox = gtk_list_box_new();
    gtk_widget_add_css_class(listBox, "boxed-list");
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(listBox), GTK_SELECTION_NONE);

    GtkWidget *suggestionRow = adw_action_row_new();
    adw_preferences_row_set_title(ADW_PREFERENCES_ROW(suggestionRow), "By Common Friends");
    adw_action_row_add_suffix(ADW_ACTION_ROW(suggestionRow), gtk_image_new_from_icon_name("go-next-symbolic"));
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(suggestionRow), true);

    gtk_list_box_append(GTK_LIST_BOX(listBox), suggestionRow);

    GtkWidget *suggestionRow1 = adw_action_row_new();
    adw_preferences_row_set_title(ADW_PREFERENCES_ROW(suggestionRow1), "By Occupation");
    adw_action_row_add_suffix(ADW_ACTION_ROW(suggestionRow1), gtk_image_new_from_icon_name("go-next-symbolic"));
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(suggestionRow1), true);

    gtk_list_box_append(GTK_LIST_BOX(listBox), suggestionRow1);

    GtkWidget *suggestionRow2 = adw_action_row_new();
    adw_preferences_row_set_title(ADW_PREFERENCES_ROW(suggestionRow2), "By Age");
    adw_action_row_add_suffix(ADW_ACTION_ROW(suggestionRow2), gtk_image_new_from_icon_name("go-next-symbolic"));
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(suggestionRow2), true);

    gtk_list_box_append(GTK_LIST_BOX(listBox), suggestionRow2);

    return listBox;
}


GtkWidget* ui::create_properties_list_box(const Person* person) {
    GtkWidget *listBox = gtk_list_box_new();
    gtk_widget_add_css_class(listBox, "boxed-list");
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(listBox), GTK_SELECTION_NONE);

    GtkWidget *dcRow = adw_action_row_new();
    adw_preferences_row_set_title(ADW_PREFERENCES_ROW(dcRow), "Degree Centrality");
    adw_action_row_set_subtitle(ADW_ACTION_ROW(dcRow), std::to_string(graph.degreeCentralityOfPerson(person->getId())).c_str());
    // adw_action_row_add_suffix(ADW_ACTION_ROW(dcRow), gtk_image_new_from_icon_name("go-next-symbolic"));
    gtk_widget_add_css_class(dcRow, "property");
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(dcRow), false);

    gtk_list_box_append(GTK_LIST_BOX(listBox), dcRow);

    GtkWidget *ccRow = adw_action_row_new();
    adw_preferences_row_set_title(ADW_PREFERENCES_ROW(ccRow), "Clustering Coefficient");
    adw_action_row_set_subtitle(ADW_ACTION_ROW(ccRow), std::to_string(graph.clusteringCoefficient(person->getId())).c_str());
    // adw_action_row_add_suffix(ADW_ACTION_ROW(suggestionRow1), gtk_image_new_from_icon_name("go-next-symbolic"));
    gtk_widget_add_css_class(ccRow, "property");
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(ccRow), false);

    gtk_list_box_append(GTK_LIST_BOX(listBox), ccRow);

    return listBox;
}

void ui::add_header_bar(GtkWidget *box) {
    GtkWidget *headerBar = adw_header_bar_new();
    gtk_box_append(GTK_BOX(box), headerBar);
}
