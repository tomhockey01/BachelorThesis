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

standardString = [standardDrinks, standardSteps, standardFood, standardLight, standardTemp, standardHum, standardPeople, standardWork]
weightString = [weightDrinks, weightSteps, weightFood, weightLight, weightTemp, weightHum, weightPeople, weightWork]

def read_csv():
	data = pd.read_csv('GOOD_DATALOG.CSV')
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
	totalPhysicalScore = 0
	for concept, standard, weight in zip(hour[0:3], standardString[0:3], weightString[0:3]):
		#print(concept, standard, weight)
		totalPhysicalScore += (concept * weight)
	conceptList.append(totalPhysicalScore)

	totalEnvironmentalScore = 0
	for concept, standard, weight in zip(hour[3:6], standardString[3:6], weightString[3:6]):
		#print(concept, standard, weight)
		totalEnvironmentalScore += (concept * weight)
	conceptList.append(totalEnvironmentalScore)

	totalMentalScore = 0
	for concept, standard, weight in zip(hour[6:8], standardString[6:8], weightString[6:8]):
		#print(concept, standard, weight)
		totalMentalScore += (concept * weight)
	conceptList.append(totalPhysicalScore)

	return conceptList

data =read_csv()

calculatedPercentagesList = []
for index, row in data.iterrows():
	singleRow = row.to_string(index=False, dtype=False).split('\n')
	relevantData = list(map(float,singleRow[0:8]))
	percentages = calculatePercentages(relevantData)
	calculatedPercentagesList.append(percentages)
	
for hour in calculatedPercentagesList:
	#print(hour)
	a = calculateTotal(hour)
	
	print(a)
	






