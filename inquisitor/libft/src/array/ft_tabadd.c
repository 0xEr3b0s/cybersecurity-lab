#include "libft.h"

char	**ft_tabadd(char **tab, const char *str)
{
	char	**res;
	size_t	len;
	size_t	i;

	len = ft_tablen(tab);
	res = (char **)malloc((len + 2) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = tab[i];
		i++;
	}
	res[i] = ft_strdup(str);
	if (!res[i])
		return (free(res), NULL);
	res[i + 1] = NULL;
	free(tab);
	return (res);
}
