// File: examplewindow.cc (For use with gtkmm 3, not gtkmm 2)
// https://docs.huihoo.com/gtkmm/programming-with-gtkmm-3/3.2.1/en/sec-treeview-examples.html

#include <iostream>
#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Button_Quit("Quit")
{
  set_title("Gtk::TreeView (ListStore) example");
  set_border_width(5);
  set_default_size(400, 200);

  add(m_VBox);

  //Add the TreeView, inside a ScrolledWindow, with the button underneath:
  m_ScrolledWindow.add(m_TreeView);

  //Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  m_VBox.pack_start(m_ScrolledWindow);
  m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

  m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);
  m_ButtonBox.set_border_width(5);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_button_quit) );

  //Create the Tree model:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  m_TreeView.set_model(m_refTreeModel);

  //Fill the TreeView's model
  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 1;
  row[m_Columns.m_col_name] = "Billy Bob";
  row[m_Columns.m_col_number] = 10;
  row[m_Columns.m_col_percentage] = 15;

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 2;
  row[m_Columns.m_col_name] = "Joey Jojo";
  row[m_Columns.m_col_number] = 20;
  row[m_Columns.m_col_percentage] = 40;

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 3;
  row[m_Columns.m_col_name] = "Rob McRoberts";
  row[m_Columns.m_col_number] = 30;
  row[m_Columns.m_col_percentage] = 70;

  //Add the TreeView's view columns:
  //This number will be shown with the default numeric formatting.
  m_TreeView.append_column("ID", m_Columns.m_col_id);
  m_TreeView.append_column("Name", m_Columns.m_col_name);

  m_TreeView.append_column_numeric("Formatted number", m_Columns.m_col_number,
          "%010d" /* 10 digits, using leading zeroes. */);

  //Display a progress bar instead of a decimal number:
  Gtk::CellRendererProgress* cell = Gtk::manage(new Gtk::CellRendererProgress);
  int cols_count = m_TreeView.append_column("Some percentage", *cell);
  Gtk::TreeViewColumn* pColumn = m_TreeView.get_column(cols_count - 1);
  if(pColumn)
  {
    pColumn->add_attribute(cell->property_value(), m_Columns.m_col_percentage);
  }

  //Make all the columns reorderable:
  //This is not necessary, but it's nice to show the feature.
  //You can use TreeView::set_column_drag_function() to more
  //finely control column drag and drop.
  for(guint i = 0; i < 2; i++)
  {
    Gtk::TreeView::Column* pColumn = m_TreeView.get_column(i);
    pColumn->set_reorderable();
  }

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  hide();
}
