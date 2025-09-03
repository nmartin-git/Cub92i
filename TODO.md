- refaire le raycasting pour pas qu'il soit en fonction de la minimap, plutot faire en fonction d'un tableau de float par exemple pour plus de précisions.

- faire une structure ray qui contient la distance avec le premier mur qu'il croise, quelle face il a touché, si il traverse un ennemi, si il traverse une puff, quel pourcentage du mur il a touché (pour les textures) et pareil pour les ennemis et les puffs.

- pour les ennemis, faire une structure qui contient ses coordonnées ses points de vies et ses degats, la distance avec le joueur etc etc.

- faire que les déplacements se fassent en fonction de la direction du joueur et non N S E W.

- eviter les mallocs (exemple, dans la fonction new_image).
