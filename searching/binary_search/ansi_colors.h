//
// Created by Dany on 07/24/2025.
// Copyright (c) 2025 DanyilT. All rights reserved.
// MIT License: https://github.com/DanyilT/C/blob/main/LICENSE
// This file is part of 'DanyilT/C' repo: https://github.com/DanyilT/C
//
// ANSI Color Codes for Console Output
//

#ifndef ANSI_COLORS_H
#define ANSI_COLORS_H

// Text Colors
#define RESET   "\033[0m"       // Reset to default color
#define BLACK   "\033[30m"      // Black text
#define RED     "\033[31m"      // Red text
#define GREEN   "\033[32m"      // Green text
#define YELLOW  "\033[33m"      // Yellow text
#define BLUE    "\033[34m"      // Blue text
#define MAGENTA "\033[35m"      // Magenta text
#define CYAN    "\033[36m"      // Cyan text
#define WHITE   "\033[37m"      // White text

// Text Styles
#define BOLD    "\033[1m"       // Bold text
#define DIM     "\033[2m"       // Dim text
#define ITALIC  "\033[3m"       // Italic text
#define UNDERLINE "\033[4m"     // Underline text

// Background Colors
#define BG_BLACK   "\033[40m"   // Black background
#define BG_RED     "\033[41m"   // Red background
#define BG_GREEN   "\033[42m"   // Green background
#define BG_YELLOW  "\033[43m"   // Yellow background
#define BG_BLUE    "\033[44m"   // Blue background
#define BG_MAGENTA "\033[45m"   // Magenta background
#define BG_CYAN    "\033[46m"   // Cyan background
#define BG_WHITE   "\033[47m"   // White background

#endif //ANSI_COLORS_H
