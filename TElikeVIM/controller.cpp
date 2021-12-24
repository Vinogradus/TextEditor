#include "main_had.h"

Controller::Controller(Model* model)
{
	model_ = model;
}

void Controller::Start()
{
	model_->init_model();
	while (1)
	{
		switch (model_->get_current_mode())
		{
		case cModeNavigation:
			NavigationMode();
			break;

		case cModeCommand:
			CommandMode();
			break;

		case cModeInput:
			InputMode();
			break;

		case cModeSearch:
			SearchMode();
			break;

		case cModeExit:
			goto exit;
			break;

		case cModeHEX:
			HEX_mode();
			break;

		default: break;
		}
	}

exit:;

}


void Controller::NavigationMode()
{
	int push;
	DynString<char> num("1234"); num.clear();// num for <NG> command
	unsigned int number;
	while (_kbhit() == 0);
	push = _getch();
	switch (push)
	{
	case 'i':
		model_->set_current_mode(cModeInput);
		break;
	case ':':
		model_->set_current_mode(cModeCommand);
		break;
	case '/':
		model_->set_search_mode(0);//to the end
		model_->set_current_mode(cModeSearch);
		break;
	case '?':
		model_->set_search_mode(1);//to the start
		model_->set_current_mode(cModeSearch);
		break;
	case 'I':
		model_->go_to_begin();
		model_->set_current_mode(cModeInput);
		break;
	case 'A':
		if (!(model_->is_empty())) model_->go_to_end();
		model_->set_current_mode(cModeInput);
		break;
	case 'S':
		model_->go_right_for_S();
		number = model_->get_x();
		while (number > 1)
		{
			model_->delete_letter(1);
			number--;
		}
		//model_->go_right_for_S();

		model_->set_current_mode(cModeInput);
		break;
	case 'r':
		if(model_->is_empty()) break;
		while (_kbhit() == 0);
		push = _getch();
		model_->coord_x_plus();
		model_->delete_letter(1);
		model_->add_letter(static_cast<char> (push));
		model_->coord_x_minus();
		break;
	case 224:
		unsigned int prov;
		prov = navigation_buttons();
		break;
	case '^':
		model_->go_to_begin();
		break;
	case '$':
		model_->go_to_end();
		break;
	case 'w':
		model_->go_right();
		model_->reload_xy();
		break;
	case 'b':
		model_->go_left_for_b();
		model_->reload_xy();
		break;
	case 'g':
		while (_kbhit() == 0);
		push = _getch();
		if (push == 'g')
		{
			model_->go_up();
		}
		break;
	case 'G':
		model_->go_down();
		break;
	case 48:
	case 49:
	case 50:
	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
	case 57:
		while (push != 'G')
		{
			num.append(1, push);
			while (_kbhit() == 0);
			push = _getch();
		}
		number = atoi(num.c_str());
		model_->command_num(number);
		break;

	case 'x':
		model_->delete_letter(0);
		break;
	case 'd': //commands <dd> and <div>
		while (_kbhit() == 0);
		push = _getch();
		if (push == 'd')
		{
			model_->set_copy_flag(0);
			model_->copy_line();
			model_->delete_line();
		}
		else if (push == 'i')
		{
			while (_kbhit() == 0);
			push = _getch();
			if (push == 'w')
			{
				model_->diw_command();
			}
		}
		break;
	case 'y':
		while (_kbhit() == 0);
		push = _getch();
		if (push == 13) //Enter
		{
			model_->set_copy_flag(0);
			model_->copy_line();
		}
		else if (push == 'w')
		{
			int count;
			model_->set_copy_flag(1);
			count = model_->copy_word();
			model_->set_word_size(count);
		}
		break;
	case 'p':
		model_->insert();
		break;
	case 88:
		model_->switch_on_hex();
		model_->set_current_mode(cModeHEX);
		break;
	default:
		break;
	}
}

void Controller::InputMode()
{
	int push;
	while (_kbhit() == 0);
	push = _getch();
	switch (push)
	{
	case 8: //backspace
		model_->delete_letter(1);
		break;
	case 13: //Enter
		model_->add_enter();
		break;
	case 27: //ESC
		model_->set_current_mode(cModeNavigation);
		break;
	case 224:
		unsigned int prov;
		prov = navigation_buttons();
		break;
	default:
		model_->add_letter(static_cast<char> (push));
		break;
	}
}

void Controller::CommandMode()
{
	DynString<char> command_line("123"); command_line.clear();
	int push;
	while (_kbhit() == 0);
	push = _getch();
	while (push != 27 && push != 13) //Enter and ESC
	{
		if (push == 8)
		{
			if (command_line.length())
			{
				command_line.erase(command_line.length(), 1);
				model_->NotifyUpdateCommand(command_line);
			}
		}
		else
		{
			command_line.append(1, static_cast<char> (push));
			model_->NotifyUpdateCommand(command_line);
		}
		while (_kbhit() == 0);
		push = _getch();
	}
	if (push == 13)
	{
		get_command(command_line);
	}
	else if (push == 27)
	{
		model_->set_current_mode(cModeNavigation);
	}
}

void Controller::get_command(DynString<char> command_line)
{
	if (command_line[0] == 'x') model_->command_x();
	else if (command_line[0] == 'o')
	{
		DynString<char> filename("123"); filename.clear();
		command_line.substr(2);
		filename = command_line;
		model_->get_filename(filename);
		model_->command_o();
	}
	else if (command_line[0] == 'w')
	{
		if (command_line[1] == 'q')
		{
			if (command_line[2] == '!')
				model_->command_q();
		}
		else if (command_line[1] == ' ')
		{
			DynString<char> filename("123"); filename.clear();
			command_line.substr(2);
			filename = command_line;
			model_->command_wf(filename);
		}
		else
		{
			model_->command_w();
		}
	}
	else if (command_line[0] == 'q')
	{
		if (command_line[1] == '!') model_->command_qs();
		else model_->command_q_();
	}
	else if (command_line[0] == 'h') model_->command_h();
	else
	{
		char symb;
		symb = command_line[0];
		if (symb >= 48 && symb <= 57) //the number
		{
			unsigned int num = atoi(command_line.c_str());
			model_->command_num(num);
		}
		else return;
	}
}

unsigned int Controller::navigation_buttons()
{
	int push = -1;
	while (_kbhit() == 0);
	push = _getch();
	switch (push)
	{
	case -1:
		return 0;//no navigation button
		break;
	case 72:
		model_->button_up();
		break;
	case 73:
		model_->page_up();
		break;
	case 75:
		model_->button_left();
		break;
	case 77:
		model_->button_right();
		break;
	case 80:
		model_->button_down();
		break;
	case 81:
		model_->page_down();
		break;
	case 83:
		model_->delete_letter(0);
		break;
	default:
		break;
	}
}

void Controller::SearchMode()
{
	DynString<char> search_line("123"); search_line.clear();
	int push;
	while (_kbhit() == 0);
	push = _getch();
	while (push != 27 && push != 13)
	{
		if (push == 8)
		{
			if (search_line.length())
			{
				search_line.erase(search_line.length(), 1);
				model_->NotifyUpdateCommand(search_line);
			}
		}
		else
		{
			search_line.append(1, static_cast<char> (push));
			model_->NotifyUpdateCommand(search_line);
		}

		while (_kbhit() == 0);
		push = _getch();
	}

	if (push == 13)
	{
		if (model_->get_search_mode() != 2)
		{
			model_->get_search_string(search_line);
			model_->do_search();
			while (push != 27)
			{
				while (_kbhit() == 0);
				push = _getch();
				if (push == 'n')
				{
					model_->do_search();
				}
				else if (push == 'N')
				{
					model_->reset_search_mode();
					model_->do_search();
				}
			}
		}
		else
		{
			model_->get_search_string(search_line);
			model_->hex_do_search();
			model_->set_current_mode(cModeHEX);
		}
		if (push == 27)
		{
			if (model_->get_search_mode() != 2)
			{
				model_->set_current_mode(cModeNavigation);
			}
			else model_->set_current_mode(cModeHEX);
		}
	}
	else if (push == 27)
	{
		if (model_->get_search_mode() != 2)
		{
			model_->set_current_mode(cModeNavigation);
		}
		else model_->set_current_mode(cModeHEX);
	}
}


unsigned int Controller::hex_navigation()
{
	int push = -1;
	while (_kbhit() == 0);
	push = _getch();
	switch (push)
	{
	case -1:
		return 0;//no navigation button
		break;
	case 72:
		model_->hex_button_up();
		break;
	case 75:
		model_->hex_button_left();
		break;
	case 77:
		model_->hex_button_right();
		break;
	case 80:
		model_->hex_button_down();
		break;
	}
}

void Controller::HEX_mode()
{
	unsigned int prov;
	DynString <char> num("123"); num.clear(); unsigned int number;
	int push;
	while (_kbhit() == 0);
	push = _getch(); int push_r;
	switch (push)
	{
	case 48:
	case 49:
	case 50:
	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
	case 57:
		while (push != 'G')
		{
			num.append(1, push);
			while (_kbhit() == 0);
			push = _getch();
		}
		number = atoi(num.c_str());
		model_->hex_command_num(number);
		break;

	case 224:
		prov = hex_navigation();
		break;
	case 88:
		model_->switch_on_normal();
		model_->set_current_mode(cModeNavigation);
		break;
	case '^':
		while (_kbhit() == 0);
		push_r = _getch();
		if (push_r == 'x')
		{
			model_->set_search_mode(2);
			model_->set_current_mode(cModeSearch);
		}
		break;
	case 'r':
		while (_kbhit() == 0);
		push_r = _getch();
		model_->hex_r(static_cast<char> (push_r));
		break;

	default:
		break;
	}
}



