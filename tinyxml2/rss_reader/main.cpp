// original : https://github.com/mehdi-farsi/CPP_rss_reader

#include	<iostream>
#include	"RssReader.hh"

int		main(int ac, char **av)
{
  RssReader	*rss;

  if (ac < 2)
    {
      std::cout << "Usage: " << av[0] << " XML_FILE_NAME" << std::endl;
      return (EXIT_FAILURE);
    }
  if (ac == 2)
    {
      rss = new RssReader(av[1]);
      return (rss->dump_items());
    }
  else
    {
      rss = new RssReader(ac, av);
      return (rss->dump_items());
    }
  return (EXIT_SUCCESS);
}
