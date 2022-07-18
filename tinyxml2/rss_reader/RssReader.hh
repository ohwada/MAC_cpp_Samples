// original : https://github.com/mehdi-farsi/CPP_rss_reader

#ifndef		__RSSREADER_HH__
#define		__RSSREADER_HH__

#include	<tinyxml.h>

class		RssReader
{
private:
  char		**_av;
  int		_ac;
  TiXmlDocument	*_document;
  TiXmlHandle	*_handle;
  void		dump_item(TiXmlElement const *);
  void		dump_channel_header(TiXmlElement const *);
  void		dump_content_tag(TiXmlElement const *, std::string const &);
  int		dump_one_file();
  int		dump_multiple_files();
  void		open_file(int);
  int		getCommand(int);
public:
  RssReader(const char *);
  RssReader(int ac, char **av);
  int		dump_items();
};

void		mode_raw(int);

#endif		/* __RSSREADER_HH__ */
