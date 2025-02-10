/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aauberti <aauberti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:33:31 by aauberti          #+#    #+#             */
/*   Updated: 2025/02/10 12:33:32 by aauberti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

/*	Text Modifications	*/
# define RESET		"\e[0m"
# define BOLD		"\e[1m"
# define DIM		"\e[2m"
# define ITALIC		"\e[3m"
# define UNDERL		"\e[4m"
# define BLINK		"\e[5m"
# define REV		"\e[7m"
# define HIDDEN		"\e[8m"
# define CROSSED	"\e[9m"

/*	Regular Colors		*/
# define BLACK		"\e[0;30m"
# define RED		"\e[0;31m"
# define GREEN		"\e[0;32m"
# define YELLOW		"\e[0;33m"
# define BLUE		"\e[0;34m"
# define PURPLE		"\e[0;35m"
# define CYAN		"\e[0;36m"
# define WHITE		"\e[0;37m"

/*	Bold Colors			*/
# define B_BLACK	"\e[1;30m"
# define B_RED		"\e[1;31m"
# define B_GREEN	"\e[1;32m"
# define B_YELLOW	"\e[1;33m"
# define B_BLUE		"\e[1;34m"
# define B_MAGENTA	"\e[1;35m"
# define B_CYAN		"\e[1;36m"
# define B_WHITE	"\e[1;37m"

/*	Background Colors	*/
# define BG_BLACK	"\e[40m"
# define BG_RED		"\e[41m"
# define BG_GREEN	"\e[42m"
# define BG_YELLOW	"\e[43m"
# define BG_BLUE	"\e[44m"
# define BG_MAGENTA	"\e[45m"
# define BG_CYAN	"\e[46m"
# define BG_WIHTE	"\e[47m"

#endif
