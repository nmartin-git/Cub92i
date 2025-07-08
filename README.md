- - Parsing
- - Fenetre
- - Bonus

- - puff change differentes couleurs
- - puff bonus puff malus (plus vite, en noir et blanc, devenir tout petit (grandir les murs autour), qui cache la minimap etc)
- - boss 92i qui lance des attaques pieds vernis blanc
- - boss paqueta avec musique plus fort quand il se rapproche
- - el mordjene pour les pv
- - minimap qui change de couleurs a chaque puff
- - pouvoir mettre la map en gros (changer MINIMAP_SIZE)
- - ajouter fleche de direction au curseur
- - chicha mystere qui donne pouvoirs et garder puff seulement pour gagner le niveau


	int	x_wall;
	int	y_wall;

	if (pos->x == TAN_ERR || pos->y == TAN_ERR)
		return (1);
	x_wall = (pos->x - MINIMAP_SIZE / 15) / minimap->pxl_size;
	y_wall = (pos->y - MINIMAP_SIZE / 15) / minimap->pxl_size;
	if (x_wall == data->map->col - 1 && y_wall == data->map->row - 1)
        return (1);
	if (x_wall >= data->map->col || y_wall >= data->map->row
		|| x_wall < 0 || y_wall < 0)
		return (1);
	if (data->map->map[y_wall][x_wall] == WALL)
		return (1);
	else
		return (0);