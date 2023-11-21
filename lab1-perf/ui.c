#include "ui.h"
#include "io.h"
#include "analyze.h"

#include <stdbool.h>
#include <stdio.h>

//
// Private
//
static void ui_invalid_input()
{
	printf("info> bad input\n");
}

static void ui_exit()
{
	printf("info> bye\n");
}

static char ui_get_choice()
{
	char buf[3];

	printf("input> ");
	return read_line(buf, 3) ? buf[0] : 0;
}

static void ui_line(char c, int n)
{
	while (n-- > 0) {
		putchar(c);
	}
	putchar('\n');
}

static void ui_menu_options(const char *options[], int num_options)
{
	int i;

	for (i=0; i<num_options; i++) {
		printf("    %c) %s\n", 'a'+i, options[i]);
	}
}

static void ui_menu()
{
	const char *options[] = {
		"Menu",
		"Exit\n",
		"Bubble sort best case",
		"Bubble sort worst case",
		"Bubble sort avarage case\n",
		"Insertion sort best case",
		"Insertion sort worst case",
		"Insertion sort avarage case\n",
		"Quick sort best case",
		"Quick sort worst case",
		"Quick sort avarage case\n",
		"linear search best case",
		"linear search worst case",
		"linear search avarage case\n",
		"Binary search best case",
		"Binary search worst case",
		"Binary search avarage case"
	};

	ui_line('=', MENU_WIDTH);
	ui_menu_options(options, sizeof(options) / sizeof(char *));
	ui_line('-', MENU_WIDTH);
}

//
// Public
//
void ui_run()
{
	bool running, show_menu;
	result_t result[RESULT_ROWS];
	
	show_menu = true;
	running = true;
	while (running) {
		if (show_menu) {
			show_menu = false;
			ui_menu();
		}
		switch (ui_get_choice()) {
			// House keeping
			case 'a':
				show_menu = true;
				break;
			case 'b':
				running = false;
				break;
			// Bubble sort
			case 'c':
				printf("\t\t\t\tBubble sort: best\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
				benchmark(bubble_sort_t, best_t, result, RESULT_ROWS);
				break;
			case 'd':
				printf("\t\t\t\tBubble sort: worst\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
				benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS);
				break;
			case 'e':
				printf("\t\t\t\tBubble sort: average\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
				benchmark(bubble_sort_t, average_t, result, RESULT_ROWS);
				break;
			// Insertion sort
			case 'f':
				printf("\t\t\t\tInsertion sort: best\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
				benchmark(insertion_sort_t, best_t, result, RESULT_ROWS);
				break;
			case 'g':
				printf("\t\t\t\tInsertion sort: worst\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
				benchmark(insertion_sort_t, worst_t, result, RESULT_ROWS);
				break;
			case 'h':
				printf("\t\t\t\tInsertion sort: average\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
				benchmark(insertion_sort_t, average_t, result, RESULT_ROWS);
				break;
			// Quick sort
			case 'i':
				printf("\t\t\t\tQuick sort: best\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
				benchmark(quick_sort_t, best_t, result, RESULT_ROWS);
				break;
			case 'j':
				printf("\t\t\t\tQuick sort: worst\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
				benchmark(quick_sort_t, worst_t, result, RESULT_ROWS);
				break;
			case 'k':
				printf("\t\t\t\tQuick sort: average\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
				benchmark(quick_sort_t, average_t, result, RESULT_ROWS);
				break;
			// Linear search
			case 'l':
				printf("\t\t\t\tLinear search: best\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
				benchmark(linear_search_t, best_t, result, RESULT_ROWS);
				break;
			case 'm':
				printf("\t\t\t\tLinear search: worst\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
				benchmark(linear_search_t, worst_t, result, RESULT_ROWS);
				break;
			case 'n':
				printf("\t\t\t\tLinear search: average\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
				benchmark(linear_search_t, average_t, result, RESULT_ROWS);
				break;
			// Binary search
			case 'o':
				printf("\t\t\t\tBinary search: best\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
				benchmark(binary_search_t, best_t, result, RESULT_ROWS);
				break;
			case 'p':
				printf("\t\t\t\tBinary search: worst\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
				benchmark(binary_search_t, worst_t, result, RESULT_ROWS);
				break;
			case 'q':
				printf("\t\t\t\tBinary search: average\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
				benchmark(binary_search_t, average_t, result, RESULT_ROWS);
				break;
			// Invalid input
			default:
				show_menu = false;
				ui_invalid_input();
				break;
		}
	}
	ui_exit();
}
