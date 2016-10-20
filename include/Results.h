#ifndef RESULTS_H
#define RESULTS_H


class Results
{
	public:
		Results(int *distance, int *previous);
		virtual ~Results();
		int *getDistances();
		int *getPreviouses();
	protected:

	private:
		int *distance;
		int *previous;
};

#endif // RESULTS_H
