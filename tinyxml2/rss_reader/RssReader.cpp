// original : https://github.com/mehdi-farsi/CPP_rss_reader

#include	<termios.h>
#include	<unistd.h>
#include	<iostream>
#include	"RssReader.hh"

RssReader::RssReader(int ac, char **av): _av(av), _ac(ac)
{
  
}

RssReader::RssReader(const char *filename)
{
  this->_document = new TiXmlDocument(filename);
  this->_handle = new TiXmlHandle(this->_document);
  this->_ac = 0;

  if (!this->_document->LoadFile())
    {
      std::cout << "error N°" << this->_document->ErrorId() << ": "
		<< this->_document->ErrorDesc() << std::endl;
      exit(1);
    }
  if (this->_handle == NULL)
    {
      std::cout << "Unable to access this node !" << std::endl;
      exit(1);
    }
}

void		RssReader::open_file(int index)
{
  this->_document = new TiXmlDocument(this->_av[index]);
  this->_handle = new TiXmlHandle(this->_document);

  if (!this->_document->LoadFile())
    {
      std::cout << "error N°" << this->_document->ErrorId() << ": "
		<< this->_document->ErrorDesc() << std::endl;
      exit(1);
    }
  if (this->_handle == NULL)
    {
      std::cout << "Unable to access this node !" << std::endl;
      exit(1);
    }
}

int		RssReader::dump_one_file()
{
  TiXmlElement	*current_node = 
    this->_handle->FirstChildElement("rss").FirstChildElement("channel").Element();

  if (current_node == NULL)
    {
      std::cout << "No item !" << std::endl;
      return (EXIT_FAILURE);
    }

  std::cout << "\033[2J\033[1;1H";
  this->dump_channel_header(current_node);

  current_node = this->_handle->FirstChildElement("rss").FirstChildElement("channel")
    .FirstChildElement("item").Element();

  if (current_node == NULL)
    {
      std::cout << "No item !" << std::endl;
      return (EXIT_FAILURE);
    }
  for (; current_node; (current_node = current_node->NextSiblingElement()))
    {
      if (current_node->NoChildren() == false)
	{
	  this->dump_item(current_node);
	}
    }
  return (EXIT_SUCCESS);
}

int		RssReader::getCommand(int i)
{
  char		c;

  c = getchar();

  if (c == 'q')
    return (-2);
  else if (c == 'n')
    {
      if ((i + 1) >= this->_ac)
	i = 1;
      else
	i++;
    }
  else if (c == 'p')
    {
      if (i > 1)
	i--;
    }
  else
    i = -1;
  std::cout << "\r\n ac:" << this->_ac << " c:" << c << " i:" << i << "\r\n";  
  return (i);
}	

int		RssReader::dump_multiple_files()
{
  TiXmlElement	*current_node;
  int idx = 1;
  std::cout << "\033[2J\033[1;1H";
  mode_raw(1); // Mode raw: buffering without 'Enter' key
  while (idx != -2) // Code to QUIT program
    {
      if (idx != -1)
	{
	  std::cout << "\033[2J\033[1;1H";
	  this->open_file(idx);
	  current_node = 
	    this->_handle->FirstChildElement("rss")
	    .FirstChildElement("channel").Element();
	  if (current_node == NULL)
	    {
	      std::cout << "No item !" << std::endl;
	      return (EXIT_FAILURE);
	    }
	  this->dump_channel_header(current_node);
	  current_node = this->_handle->FirstChildElement("rss")
	    .FirstChildElement("channel")
	    .FirstChildElement("item").Element();
	  if (current_node == NULL)
	    {
	      std::cout << "No item !" << std::endl;
	      return (EXIT_FAILURE);
	    }
	  for (; current_node; (current_node = current_node->NextSiblingElement()))
	    {
	      if (current_node->NoChildren() == false)
		this->dump_item(current_node);
	    }
	}

      idx = getCommand(idx);
    }
  mode_raw(0); // Mode Cooked
  return (EXIT_SUCCESS);
}

int		RssReader::dump_items()
{
  if (this->_ac == 0)
    {
      return (this->dump_one_file());
    }
  else
    {
      return (this->dump_multiple_files());
    }
}

void		RssReader::dump_channel_header(TiXmlElement const *channel)
{
  std::string	sep(40, '*');

  dump_content_tag(channel, "title");
  dump_content_tag(channel, "description");
  dump_content_tag(channel, "lastBuildDate");
  dump_content_tag(channel, "link");
  std::cout << sep << std::endl << std::endl;
}

void		RssReader::dump_item(TiXmlElement const *item)
{
  std::string	sep(40, '-');

  dump_content_tag(item, "title");
  dump_content_tag(item, "description");
  dump_content_tag(item, "pubDate");
  dump_content_tag(item, "link");
  std::cout << sep << "\r\n\r\n";
}

void		RssReader::dump_content_tag(TiXmlElement const *node,
					    std::string const &elem)
{
    if (node->FirstChildElement(elem) != NULL)
    {
      std::cout << node->FirstChildElement(elem)->GetText() << "\r\n";
    }
}

void mode_raw(int activer)
{
  static struct termios cooked;
  static int raw_actif = 0;
  struct termios raw;

  if (raw_actif == activer)
    return;

  if (activer)
    {
      tcgetattr(STDIN_FILENO, &cooked);
      raw = cooked;
      cfmakeraw(&raw);
      tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    }
  else
    tcsetattr(STDIN_FILENO, TCSANOW, &cooked);
  raw_actif = activer;
}
