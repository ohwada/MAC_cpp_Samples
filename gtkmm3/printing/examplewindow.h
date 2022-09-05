// File: examplewindow.h (For use with gtkmm 3, not gtkmm 2)
// https://docs.huihoo.com/gtkmm/programming-with-gtkmm-3/3.2.1/en/sec-printing-example.html

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <memory>
#include <vector>

#include <pangomm.h>
#include <gtkmm.h>

class PrintFormOperation;

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:

  void build_main_menu();

  void print_or_preview(Gtk::PrintOperationAction print_action);

  //PrintOperation signal handlers.
  //We handle these so can get necessary information to update the UI or print settings.
  //Our derived PrintOperation class also overrides some default signal handlers.
  void on_printoperation_status_changed(const Glib::RefPtr<PrintFormOperation>& operation);

  void on_printoperation_done(Gtk::PrintOperationResult result, const Glib::RefPtr<PrintFormOperation>& operation);

  //Action signal handlers:
  void on_menu_file_new();
  void on_menu_file_page_setup();
  void on_menu_file_print_preview();
  void on_menu_file_print();
  void on_menu_file_quit();

  //Printing-related objects:
  Glib::RefPtr<Gtk::PageSetup> m_refPageSetup;
  Glib::RefPtr<Gtk::PrintSettings> m_refSettings;


  //Child widgets:
  Gtk::Box m_VBox;
  Gtk::Table m_Table;

  Gtk::Label m_NameLabel;
  Gtk::Entry m_NameEntry;

  Gtk::Label m_SurnameLabel;
  Gtk::Entry m_SurnameEntry;

  Gtk::Label m_CommentsLabel;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::TextView m_TextView;
  
  Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;

  unsigned m_ContextId;
  Gtk::Statusbar m_Statusbar;

  Glib::RefPtr<Gtk::UIManager> m_refUIManager;
  Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
};

#endif //GTKMM_EXAMPLEWINDOW_H
