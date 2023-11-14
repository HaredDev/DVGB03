#include "ui.h"
#include "io.h"
#include "analyze.h"

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
	char buffer[3];

	printf("input> ");
	// read_line(buffer, 3) ? true : false
	return read_line(buffer, 3) ? buffer[0] : 0;
}

static void ui_line(char c, int n)
{
	while (n-- > 0)
	{
		putchar(c);
	}
	putchar('\n');
}

static void ui_menu_options(const char *options[], int num_options)
{
	int i;

	for (i = 0; i < num_options; i++)
	{
		printf("    %c) %s\n", 'a' + i, options[i]);
	}
}

static void ui_menu()
{
	const char *options[] = {
		"Menu",
		"Exit\n",
		"Bubble sort best case",
		"Bubble sort worst case",
		"Bubble sort average case\n",
		"Insertion sort best case",
		"Insertion sort worst case",
		"Insertion sort average case\n",
		"Quick sort best case",
		"Quick sort worst case",
		"Quick sort average case\n",
		"Linear search best case",
		"Linear search worst case",
		"Linear search average case\n",
		"Binary search best case",
		"Binary search worst case",
		"Binary search average case",
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
	while (running)
	{
		if (show_menu)
		{
			show_menu = false;
			ui_menu();
		}
		switch (ui_get_choice())
		{
		// House keeping
		case 'a':
			show_menu = true;
			break;
		case 'b':
			running = false;
			break;
		// Bubble sort
		case 'c':
			// bubble: best result
			printf("\t\t\t\tBubble sort: best\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
			benchmark(bubble_sort_t, best_t, result, RESULT_ROWS);
			break;
		case 'd':
			// bubble: worst result
			printf("\t\t\t\tBubble sort: worst\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
			benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS);
			break;
		case 'e':
			// bubble: average result
			printf("\t\t\t\tBubble sort: average\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
			benchmark(bubble_sort_t, average_t, result, RESULT_ROWS);
			break;
		// Insertion sort
		case 'f':
			// insertion: best result
			printf("\t\t\t\tInsertion sort: best\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
			benchmark(insertion_sort_t, best_t, result, RESULT_ROWS);
			break;
		case 'g':
			// insertion: worst result
			printf("\t\t\t\tInsertion sort: worst\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
			benchmark(insertion_sort_t, worst_t, result, RESULT_ROWS);
			break;
		case 'h':
			// insertion: average result
			printf("\t\t\t\tInsertion sort: average\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
			benchmark(insertion_sort_t, average_t, result, RESULT_ROWS);
			break;
		// Quick sort
		case 'i':
			// quick: best result
			printf("\t\t\t\tQuick sort: best\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
			benchmark(quick_sort_t, best_t, result, RESULT_ROWS);
			break;
		case 'j':
			// quick: worst result
			printf("\t\t\t\tQuick sort: worst\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
			benchmark(quick_sort_t, worst_t, result, RESULT_ROWS);
			break;
		case 'k':
			// quick: average result
			printf("\t\t\t\tQuick sort: average\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
			benchmark(quick_sort_t, average_t, result, RESULT_ROWS);
			break;
		// Linear search
		case 'l':
			// linear search: best result
			printf("\t\t\t\tLinear search: best\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
			benchmark(linear_search_t, best_t, result, RESULT_ROWS);
			break;
		case 'm':
			// linear search: worst result
			printf("\t\t\t\tLinear search: worst\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
			benchmark(linear_search_t, worst_t, result, RESULT_ROWS);
			break;
		case 'n':
			// linear search: average result
			printf("\t\t\t\tLinear search: average\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
			benchmark(linear_search_t, average_t, result, RESULT_ROWS);
			break;
		// Binary search
		case 'o':
			// binary search: best result
			printf("\t\t\t\tBinary search: best\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
			benchmark(binary_search_t, best_t, result, RESULT_ROWS);
			break;
		case 'p':
			// binary search: worst result
			printf("\t\t\t\tBinary search: worst\t\t\t\t\nsize\t\ttime T(s)\t\tT/logn\t\tT(n)\t\tT/nLog\n¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
			benchmark(binary_search_t, worst_t, result, RESULT_ROWS);
			break;
		case 'q':
			// binary search: average result
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
