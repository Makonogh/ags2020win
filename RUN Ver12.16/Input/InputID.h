#pragma once

enum class INPUT_ID// :型　　型の指定が可能
{
	UP,
	DOWN,
	ACTION,
	MAX,
};

INPUT_ID begin(INPUT_ID);
INPUT_ID end(INPUT_ID);
INPUT_ID operator*(INPUT_ID key);
INPUT_ID operator++(INPUT_ID& key);