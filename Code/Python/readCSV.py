import pandas as pd

standardDrinks = 15
standardPeople = 15
standardLight = 115
standardTemp = 21
standardHum = 20
standardSteps = 15
standardFood = 15
standardWork = 15

thresDrinks = 0.5
thresPeople = 0.5
thresLight = 0.5
thresTemp = 0.5
thresHum = 0.5
thresSteps = 0.5
thresFood = 0.5
thresWork = 0.5

weightDrinks = 0.5
weightPeople = 0.5
weightLight = 0.5
weightTemp = 0.5
weightHum = 0.5
weightSteps = 0.5
weightFood = 0.5
weightWork = 0.5

standardString = [standardDrinks, standardPeople, standardLight, standardTemp, standardHum, standardSteps, standardFood, standardWork]
threshString = [thresDrinks, thresPeople, thresLight, thresTemp, thresHum, thresSteps, thresFood, thresWork]
weightString = [weightDrinks, weightPeople, weightLight, weightTemp, weightHum, weightSteps, weightFood, weightWork]

def read_csv():
	data = pd.read_csv('TESTDATA.CSV')
	return data

def getRow(rowNumber):
	return data.loc[rowNumber]

def calculateScores(relevantData):
	scorelist=[]
	for i, standard in zip(relevantData, standardString):
		scorelist.append(i/standard)

	print(scorelist)


data =read_csv()

for index, row in data.iterrows():
	singleRow = row.to_string(index=False, dtype=False).split('\n')
	relevantData = list(map(int,singleRow[0:8]))
	calculateScores(relevantData)

print(thresDrinks)
	




