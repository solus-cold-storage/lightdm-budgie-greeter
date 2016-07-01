/*
 * This file is part of lightdm-budgie-greeter.
 *
 * Copyright © 2016 Ikey Doherty <ikey@solus-project.com>
 *
 * lightdm-budgie-greeter is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 */

#include <budgie-desktop/theme.h>

#include "greeter-window.h"
#include "util.h"

struct BudgieGreeterWindowPrivate {
        GtkWidget *top_panel;
        GtkWidget *top_revealer;
        GtkWidget *session_chooser;
        GtkWidget *form;
        GtkWidget *form_revealer;
        GtkWidget *password_box;
        gboolean first_map;
};

/**
 * implemented down the bottom
 */
static void budgie_greeter_window_init(BudgieGreeterWindow *self);
static void budgie_greeter_window_create_panel(BudgieGreeterWindow *self);
static void budgie_greeter_window_create_form(BudgieGreeterWindow *self);
static void budgie_greeter_window_init_css(void);

G_DEFINE_TYPE_WITH_PRIVATE(BudgieGreeterWindow, budgie_greeter_window, GTK_TYPE_WINDOW)

GtkWidget *budgie_greeter_window_new()
{
        return g_object_new(BUDGIE_TYPE_GREETER_WINDOW, NULL);
}

/**
 * Just hook up quit for now so we can hack-test the UI
 */
static gboolean budgie_greeter_window_delete(__budgie_unused__ GtkWidget *widget,
                                             __budgie_unused__ gpointer userdata)
{
        gtk_main_quit();
        return GDK_EVENT_STOP;
}

/**
 * Handle first map transition
 */
static gboolean budgie_greeter_window_first_map(BudgieGreeterWindow *self)
{
        gtk_revealer_set_reveal_child(GTK_REVEALER(self->priv->top_revealer), TRUE);
        gtk_revealer_set_reveal_child(GTK_REVEALER(self->priv->form_revealer), TRUE);
        gtk_widget_grab_focus(self->priv->password_box);
        return FALSE;
}

static gboolean budgie_greeter_window_map(BudgieGreeterWindow *self,
                                          __budgie_unused__ gpointer userdata)
{
        if (!self->priv->first_map) {
                g_timeout_add(250, (GSourceFunc)budgie_greeter_window_first_map, self);
                self->priv->first_map = TRUE;
        }
        return GDK_EVENT_PROPAGATE;
}

/**
 * Initialise our GreeterWindow correctly
 */
static void budgie_greeter_window_init(BudgieGreeterWindow *self)
{
        GtkStyleContext *context = NULL;
        GdkVisual *visual = NULL;
        GdkScreen *screen = NULL;
        GtkWidget *layout = NULL;

        self->priv = budgie_greeter_window_get_instance_private(self);
        g_signal_connect(G_OBJECT(self),
                         "delete-event",
                         G_CALLBACK(budgie_greeter_window_delete),
                         NULL);

        /* Handle mapping */
        g_signal_connect(G_OBJECT(self), "map-event", G_CALLBACK(budgie_greeter_window_map), NULL);

        /* Set up an RGBA visual */
        screen = gdk_screen_get_default();
        visual = gdk_screen_get_rgba_visual(screen);
        if (visual) {
                gtk_widget_set_visual(GTK_WIDGET(self), visual);
        } else {
                fprintf(stderr, "Cannot set visual\n");
        }

        /* Load the CSS in */
        budgie_greeter_window_init_css();

        /* Some initial presentation cruft. */
        gtk_widget_set_size_request(GTK_WIDGET(self), 1024, 768);
        gtk_window_set_position(GTK_WINDOW(self), GTK_WIN_POS_CENTER);

        /* Get some styling in place */
        context = gtk_widget_get_style_context(GTK_WIDGET(self));
        gtk_style_context_add_class(context, "budgie-container");
        gtk_style_context_add_class(context, "budgie-greeter-window");

        /* Sort the layout .. out */
        layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_container_add(GTK_CONTAINER(self), layout);

        /* Create the fake top panel */
        budgie_greeter_window_create_panel(self);
        gtk_box_pack_start(GTK_BOX(layout), self->priv->top_revealer, FALSE, FALSE, 0);

        /* Create the main login form */
        budgie_greeter_window_create_form(self);
        gtk_box_pack_start(GTK_BOX(layout), self->priv->form_revealer, TRUE, TRUE, 0);

        gtk_widget_show_all(GTK_WIDGET(self));
}

/**
 * Dispose of the current GreeterWindow
 */
static void budgie_greeter_window_dispose(GObject *object)
{
        /* No cleanups to be done yet */
        G_OBJECT_CLASS(budgie_greeter_window_parent_class)->dispose(object);
}

/**
 * Initialise the class members
 */
static void budgie_greeter_window_class_init(BudgieGreeterWindowClass *klazz)
{
        GObjectClass *obj_class = G_OBJECT_CLASS(klazz);
        obj_class->dispose = budgie_greeter_window_dispose;
}

/**
 * Create a panel area to emulate BudgiePanel
 */
static void budgie_greeter_window_create_panel(BudgieGreeterWindow *self)
{
        GtkWidget *ebox = NULL;
        GtkWidget *layout = NULL;
        GtkWidget *shadow = NULL;
        GtkWidget *panel_area = NULL;
        GtkStyleContext *context = NULL;
        GtkWidget *session_label = NULL;
        GtkWidget *combo = NULL;
        GtkWidget *top_revealer = NULL;

        ebox = gtk_event_box_new();
        context = gtk_widget_get_style_context(ebox);
        gtk_style_context_add_class(context, "budgie-container");
        gtk_style_context_add_class(context, "top");

        /* Fix layout */
        layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_container_add(GTK_CONTAINER(ebox), layout);

        /* Create the ""panel"" */
        panel_area = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_widget_set_valign(panel_area, GTK_ALIGN_START);
        gtk_widget_set_vexpand(panel_area, FALSE);
        context = gtk_widget_get_style_context(panel_area);
        gtk_style_context_add_class(context, "budgie-panel");
        gtk_box_pack_start(GTK_BOX(layout), panel_area, FALSE, FALSE, 0);
        gtk_widget_set_size_request(panel_area, -1, 35);

        /* Session label */
        session_label = gtk_label_new("Session");
        g_object_set(session_label, "margin-start", 12, NULL);
        gtk_box_pack_start(GTK_BOX(panel_area), session_label, FALSE, FALSE, 0);

        /* Session chooser */
        combo = gtk_combo_box_text_new();
        /* Don't eat all the panel for gawdsake */
        g_object_set(combo,
                     "margin-top",
                     2,
                     "margin-bottom",
                     2,
                     "margin-start",
                     12,
                     "halign",
                     GTK_ALIGN_START,
                     "valign",
                     GTK_ALIGN_CENTER,
                     NULL);

        gtk_box_pack_start(GTK_BOX(panel_area), combo, FALSE, FALSE, 0);
        /* Ensure sufficient internal padding so the down arrow isn't too close/derpy */
        g_object_set(gtk_bin_get_child(GTK_BIN(combo)),
                     "margin-start",
                     4,
                     "margin-end",
                     26,
                     "margin-top",
                     0,
                     "margin-bottom",
                     0,
                     NULL);
        self->priv->session_chooser = combo;

        /* Dumb content */
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Budgie Desktop");
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);

        /* Create the "shadow" */
        shadow = gtk_event_box_new();
        gtk_widget_set_size_request(shadow, -1, 5);
        context = gtk_widget_get_style_context(shadow);
        gtk_style_context_add_class(context, "shadow-block");

        gtk_box_pack_start(GTK_BOX(layout), shadow, FALSE, FALSE, 0);

        self->priv->top_panel = ebox;

        /* Add it into a revealer so we can expose it shortly after map */
        top_revealer = gtk_revealer_new();
        gtk_revealer_set_transition_type(GTK_REVEALER(top_revealer),
                                         GTK_REVEALER_TRANSITION_TYPE_SLIDE_DOWN);
        gtk_revealer_set_transition_duration(GTK_REVEALER(top_revealer), 600);
        gtk_container_add(GTK_CONTAINER(top_revealer), ebox);
        self->priv->top_revealer = top_revealer;
}

/**
 * Create the main login form.
 */
static void budgie_greeter_window_create_form(BudgieGreeterWindow *self)
{
        GtkWidget *layout = NULL;
        GtkWidget *image = NULL;
        GtkWidget *ebox = NULL;
        GtkStyleContext *context = NULL;
        GtkWidget *entry = NULL;
        GtkWidget *button = NULL;
        GtkWidget *hbox = NULL;
        GtkWidget *form_revealer = NULL;

        /* Use a box for the main form layout */
        layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        g_object_set(layout, "halign", GTK_ALIGN_CENTER, "valign", GTK_ALIGN_CENTER, NULL);

        image = gtk_image_new_from_icon_name("avatar-default", GTK_ICON_SIZE_DIALOG);
        gtk_image_set_pixel_size(GTK_IMAGE(image), 256);
        // image = gtk_image_new_from_file("/usr/share/pixmaps/faces/lightning.jpg");
        ebox = gtk_event_box_new();
        gtk_container_add(GTK_CONTAINER(ebox), image);
        gtk_box_pack_start(GTK_BOX(layout), ebox, FALSE, FALSE, 0);
        context = gtk_widget_get_style_context(ebox);
        gtk_style_context_add_class(context, "greeter-photo");

        /* Hbox is linked */
        hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        context = gtk_widget_get_style_context(hbox);
        gtk_style_context_add_class(context, "raven");
        gtk_style_context_remove_class(context, "background");
        gtk_widget_set_margin_top(hbox, 18);

        gtk_box_pack_start(GTK_BOX(layout), hbox, FALSE, FALSE, 0);

        /* Password */
        entry = gtk_entry_new();
        gtk_widget_set_vexpand(entry, TRUE);
        gtk_widget_set_valign(entry, GTK_ALIGN_FILL);
        gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE);
        gtk_box_pack_start(GTK_BOX(hbox), entry, TRUE, TRUE, 0);
        context = gtk_widget_get_style_context(entry);
        gtk_style_context_set_junction_sides(context, GTK_JUNCTION_RIGHT);
        self->priv->password_box = entry;

        /* Button */
        button = gtk_button_new_from_icon_name("pan-end-symbolic", GTK_ICON_SIZE_BUTTON);
        gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
        context = gtk_widget_get_style_context(button);
        gtk_style_context_set_junction_sides(context, GTK_JUNCTION_LEFT);

        /* Allow transition on form */
        form_revealer = gtk_revealer_new();
        gtk_container_add(GTK_CONTAINER(form_revealer), layout);
        gtk_revealer_set_transition_type(GTK_REVEALER(form_revealer),
                                         GTK_REVEALER_TRANSITION_TYPE_CROSSFADE);
        gtk_revealer_set_transition_duration(GTK_REVEALER(form_revealer), 1200);
        self->priv->form_revealer = form_revealer;

        self->priv->form = layout;
}

static void budgie_greeter_load_css_path(const char *path)
{
        GtkCssProvider *css_prov = NULL;
        GFile *file = NULL;
        GdkScreen *screen = NULL;

        file = g_file_new_for_uri(path);
        if (!file) {
                fprintf(stderr, "Unable to locate theme\n");
                goto end;
        }

        css_prov = gtk_css_provider_new();
        if (!gtk_css_provider_load_from_file(css_prov, file, NULL)) {
                fprintf(stderr, "Failed to load theme %s\n", path);
                goto end;
        }

        screen = gdk_screen_get_default();
        gtk_style_context_add_provider_for_screen(screen,
                                                  GTK_STYLE_PROVIDER(css_prov),
                                                  GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

end:
        if (file) {
                g_object_unref(file);
        }
}

/**
 * Set up the theming by.. basically borrowing it from Budgie :P
 */
static void budgie_greeter_window_init_css()
{
        /* TODO: Check for the HC variant! */
        char *theme_name = budgie_form_theme_path("theme.css");
        budgie_greeter_load_css_path(theme_name);
        g_free(theme_name);

        /* Load our additional resources */
        budgie_greeter_load_css_path("resource://com/solus-project/budgie/greeter/styling.css");
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 expandtab:
 * :indentSize=8:tabSize=8:noTabs=true:
 */
