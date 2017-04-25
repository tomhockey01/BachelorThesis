import pandas as pd

standardDrinks = 5
standardPeople = 10
standardLight = 115
standardTemp = 21
standardHum = 20
standardSteps = 250
standardFood = 1
standardWork = 1

thresDrinks = 0.5
thresPeople = 0.5
thresLight = 0.5
thresTemp = 0.5
thresHum = 0.5
thresSteps = 0.5
thresFood = 0.5
thresWork = 0.5

weightDrinks = 0.5
weightPeople = 0.2
weightLight = 0.3
weightTemp = 0.4
weightHum = 0.4
weightSteps = 0.7
weightFood = 0.4
weightWork = 0.6

standardString = [standardDrinks, standardSteps, standardFood, standardLight, standardTemp, standardHum, standardPeople, standardWork]
threshString = [thresDrinks, thresSteps, thresFood, thresLight, thresTemp, thresHum, thresPeople,  thresWork]
weightString = [weightDrinks, weightSteps, weightFood, weightLight, weightTemp, weightHum, weightPeople, weightWork]

def read_csv():
	data = pd.read_csv('GOOD_DATALOG.CSV')
	return data

def calculatePercentages(relevantData):
	percentageList=[]
	for i, standard in zip(relevantData, standardString):
		percentageList.append(i/standard)
	return(percentageList)


def calculateTotal(hour):
	conceptList = []
	totalPhysicalScore = 0
	for concept, thresh, weight in zip(hour[0:3], threshString[0:3], weightString[0:3]):
		#print(concept, thresh, weight)
		if (concept >= thresh):
			totalPhysicalScore += (1 * weight)
			#print("YES")
		else:
			#print("NO")
			totalPhysicalScore += (concept * weight)
	conceptList.append(totalPhysicalScore)

	totalEnvironmentalScore = 0
	for concept, thresh, weight in zip(hour[3:6], threshString[3:6], weightString[3:6]):
		#print(concept, thresh, weight)
		if (concept >= thresh):
			totalEnvironmentalScore += (1 * weight)
			#print("YES")
		else:
			#print("NO")
			totalEnvironmentalScore += (concept * weight)
	conceptList.append(totalEnvironmentalScore)

	totalMentalScore = 0
	for concept, thresh, weight in zip(hour[6:8], threshString[6:8], weightString[6:8]):
		#print(concept, thresh, weight)
		if (concept >= thresh):
			totalMentalScore += (1 * weight)
			#print("YES")
		else:
			#print("NO")
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
	





