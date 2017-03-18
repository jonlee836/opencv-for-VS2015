#include "drawOnMat.h"

void onMouseSelect(int event, int x, int y, int, void* image) {
	if (selectObject) {
		selection.x = MIN(x, origin.x);
		selection.y = MIN(y, origin.y);
		selection.width = std::abs(x - origin.x);
		selection.height = std::abs(y - origin.y);

		selection &= Rect(0, 0, ((Mat *)image)->cols, ((Mat *)image)->rows);
	}

	switch (event) {
	case CV_EVENT_LBUTTONDOWN:

		origin = Point(x, y);
		selection = Rect(x, y, 0, 0);
		selectObject = true;

		break;
	case CV_EVENT_LBUTTONUP:

		selectObject = false;
		if (selection.width > 0 && selection.height > 0)
			selectionComplete = true;
		break;
	}
}
