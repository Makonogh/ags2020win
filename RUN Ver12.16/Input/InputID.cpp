#include <type_traits>
#include "InputID.h"

INPUT_ID begin(INPUT_ID)
{
	return INPUT_ID::UP;
}

INPUT_ID end(INPUT_ID)
{
	return INPUT_ID::MAX;
}

INPUT_ID operator*(INPUT_ID key)
{
	return key;
}

INPUT_ID operator++(INPUT_ID & key)
{
	return key = static_cast<INPUT_ID>(std::underlying_type<INPUT_ID>::type(key) + 1);
}
