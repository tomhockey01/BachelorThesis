import pandas as pd

standardDrinks = 5.5
standardPeople = 3
standardLight = 115
standardTemp = 21
standardHum = 20
standardSteps = 650
standardFood = 1
standardWork = 1

weightDrinks = 0.5
weightPeople = 0.2
weightLight = 0.3
weightTemp = 0.4
weightHum = 0.4
weightSteps = 0.7
weightFood = 0.4
weightWork = 0.6

environmentWeight = 0.5

standardString = [standardDrinks, standardSteps, standardFood, standardLight, standardTemp, standardHum, standardPeople, standardWork]
weightString = [weightDrinks, weightSteps, weightFood, weightLight, weightTemp, weightHum, weightPeople, weightWork]
	
def read_csv():
	dfs={ i : pd.DataFrame.from_csv('GOOD_DATALOG'+str(i)+'.csv',sep=',',\
	header=None, index_col=None) for i in range(2)} # n files.
	panel=pd.Panel(dfs)
	data=panel.sum(axis=0)
	data = data/2

	return data

def calculatePercentages(relevantData):
	percentageList=[]
	for i, standard in zip(relevantData, standardString):
		if i < standard:
			percentageList.append(i/standard)
		else:
			percentageList.append(1)
	return(percentageList)

def calculateTotal(hour):
	conceptList = []

	totalEnvironmentalScore = 0
	for concept, standard, weight in zip(hour[3:6], standardString[3:6], weightString[3:6]):
		#print(concept, standard, weight)
		totalEnvironmentalScore += (concept * weight)
	conceptList.append(totalEnvironmentalScore)

	totalPhysicalScore = 0
	for concept, standard, weight in zip(hour[0:3], standardString[0:3], weightString[0:3]):
		#print(concept, standard, weight)
		totalPhysicalScore += (concept * weight)
	totalPhysicalScore += (totalEnvironmentalScore * environmentWeight)

	conceptList.append(totalPhysicalScore)

	totalMentalScore = 0
	for concept, standard, weight in zip(hour[6:8], standardString[6:8], weightString[6:8]):
		#print(concept, standard, weight)
		totalMentalScore += (concept * weight)
	totalPhysicalScore += (totalEnvironmentalScore * environmentWeight)

	conceptList.append(totalPhysicalScore)
	#print(conceptList)
	return conceptList

def calculatePerformance(totals):
	totalPerformance = 0
	for singleTotal in totals:
		totalPerformance += singleTotal

	return totalPerformance

data =read_csv()

calculatedPercentagesList = []
for index, row in data.iterrows():
	singleRow = row.to_string(index=False, dtype=False).split('\n')
	relevantData = list(map(float,singleRow[0:8]))
	percentages = calculatePercentages(relevantData)
	calculatedPercentagesList.append(percentages)
	
for hour in calculatedPercentagesList:
	#print(hour)
	totals = calculateTotal(hour)
	performance = calculatePerformance(totals)
	
	a = (performance - -1) / (3.5 - -1)
	print(a)





