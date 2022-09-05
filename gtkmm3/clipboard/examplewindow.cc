// File: examplewindow.cc (For use with gtkmm 3, not gtkmm 2)
// https://docs.huihoo.com/gtkmm/programming-with-gtkmm-3/3.2.1/en/sec-clipboard-examples.html

#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Label("Select cells in the table, click Copy, then open a second "
        "instance of this example to try pasting the copied data."),
  m_Table(2, 2, true),
  m_ButtonA1("A1"), m_ButtonA2("A2"), m_ButtonB1("B1"), m_ButtonB2("B2"),
  m_Button_Copy(Gtk::Stock::COPY), m_Button_Paste(Gtk::Stock::PASTE)
{
  set_title("Gtk::Clipboard example");
  set_border_width(12);

  add(m_VBox);

  m_VBox.pack_start(m_Label, Gtk::PACK_SHRINK);

  //Fill Table:
  m_VBox.pack_start(m_Table);
  m_Table.attach(m_ButtonA1, 0, 1, 0, 1);
  m_Table.attach(m_ButtonA2, 1, 2, 0, 1);
  m_Table.attach(m_ButtonB1, 0, 1, 1, 2);
  m_Table.attach(m_ButtonB2, 1, 2, 1, 2);

  //Add ButtonBox to bottom:
  m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);
  m_VBox.set_spacing(6);

  //Fill ButtonBox:
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
  m_ButtonBox.pack_start(m_Button_Copy, Gtk::PACK_SHRINK);
  m_Button_Copy.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_copy) );
  m_ButtonBox.pack_start(m_Button_Paste, Gtk::PACK_SHRINK);
  m_Button_Paste.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_paste) );

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_copy()
{
  //Build a string representation of the stuff to be copied:
  //Ideally you would use XML, with an XML parser here:
  Glib::ustring strData;
  strData += m_ButtonA1.get_active() ? "1" : "0";
  strData += m_ButtonA2.get_active() ? "1" : "0";
  strData += m_ButtonB1.get_active() ? "1" : "0";
  strData += m_ButtonB2.get_active() ? "1" : "0";

  Glib::RefPtr<Gtk::Clipboard> refClipboard = Gtk::Clipboard::get();
  refClipboard->set_text(strData);
}

void ExampleWindow::on_button_paste()
{
  //Tell the clipboard to call our method when it is ready:
  Glib::RefPtr<Gtk::Clipboard> refClipboard = Gtk::Clipboard::get();
  refClipboard->request_text(sigc::mem_fun(*this,
              &ExampleWindow::on_clipboard_text_received) );
}

void ExampleWindow::on_clipboard_text_received(const Glib::ustring& text)
{
  //See comment in on_button_copy() about this silly clipboard format.
  if(text.size() >= 4)
  {
    m_ButtonA1.set_active( text[0] == '1' );
    m_ButtonA2.set_active( text[1] == '1' );
    m_ButtonB1.set_active( text[2] == '1' );
    m_ButtonB2.set_active( text[3] == '1' );
  }
}
