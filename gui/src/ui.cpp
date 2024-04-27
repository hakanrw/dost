#include <ui.h>

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

void ui::add_header_bar(GtkWidget *box) {
    GtkWidget *headerBar = adw_header_bar_new();
    gtk_box_append(GTK_BOX(box), headerBar);
}