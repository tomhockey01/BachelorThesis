import pandas as pd
import time

standardDrinks = 5.5
standardPeople = 5
standardLight = 900
standardTemp = 20
standardHum = 19
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
	
maxPerformance = 4.60
minPerformance = 0.046

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
			#print("JA")
			percentageList.append(i/standard)
		else:
			#print("NEE")
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
	totalMentalScore += (totalEnvironmentalScore * environmentWeight)

	conceptList.append(totalMentalScore)
	#print(conceptList)
	return conceptList

def calculatePerformance(totals):
	totalPerformance = 0
	for singleTotal in totals:
		totalPerformance += singleTotal

	return totalPerformance

def fileNames(porn):
	fileName = ""
	if porn[0] == "pos":
		fileName += str("1")
		if len(porn[1])>0:
			fileName += str("p")
			for label in porn[1]:
				fileName+= str(label)
		if len(porn[2])>0:
			fileName += str("n")
			for label in porn [2]:
				fileName+=str(label)
	else:
		fileName += str("2")
		if len(porn[1])>0:
			fileName += str("p")
			for label in porn[1]:
				fileName+= str(label)
		if len(porn[2])>0:
			fileName += str("n")
			for label in porn [2]:
				fileName+=str(label)
	return fileName

		


data =read_csv()

calculatedPercentagesList = []
for index, row in data.iterrows():
	singleRow = row.to_string(index=False, dtype=False).split('\n')
	relevantData = list(map(float,singleRow[0:8]))
	percentages = calculatePercentages(relevantData)
	if (relevantData[4] < 23) and (relevantData[4] > 19):
		percentages[4] = 1
	elif (relevantData[4] >= 23):
		percentages[4] = (relevantData[4]/standardString[4])-1
		
	if (relevantData[3] < 1000) and (relevantData[3] > 800):
		percentages[3] = 1
	elif (relevantData[3] >= 1000):
		percentages[3] = (relevantData[3]/standardString[3])-1
		
	calculatedPercentagesList.append(percentages)

performances=[]
for hour in calculatedPercentagesList:
	#print(hour)
	totals = calculateTotal(hour)
	#print(totals)
	performance = calculatePerformance(totals)
	#print(performance)
	performances.append((performance - (minPerformance)) / (maxPerformance - (minPerformance))) #normalize performance

print(calculatedPercentagesList)
#print(performances)


#print("__________________________________________________")

timeCounter = 0
totalOutput = []
del calculatedPercentagesList[4:5]
for singlePercentages in calculatedPercentagesList:
	outputList = []
	if performances[timeCounter] > 0.5:
		#positive overall
		#print("YES")
		percentageCounter = 0
		negativeList = []
		positiveList = []
		del singlePercentages[4:6]
		for singlePercentage in singlePercentages:
			if singlePercentage < 0.9:
				#print("KLEINER" + str(percentageCounter))
				negativeList.append(percentageCounter)
				percentageCounter += 1
			else:
				#print("GROTER" + str(percentageCounter))
				positiveList.append(percentageCounter)
				percentageCounter += 1
		outputList.append("pos")
		outputList.append(negativeList)
		outputList.append(positiveList)
	else: 
		#negative overall
		#print("NO")
		percentageCounter = 0
		negativeList = []
		positiveList = []
		del singlePercentages[4:6]
		for singlePercentage in singlePercentages:
			if singlePercentage < 0.9:
				#print("KLEINER" + str(percentageCounter))
				negativeList.append(percentageCounter)
				percentageCounter += 1
			else:
				#print("GROTER" + str(percentageCounter))
				positiveList.append(percentageCounter)
				percentageCounter += 1
		outputList.append("neg")
		outputList.append(negativeList)
		outputList.append(positiveList)

	timeCounter += 1
	totalOutput.append(outputList)

#for image in getImageList:

def getImage():
	for i in totalOutput:
		imageName = fileNames(i)
		time.sleep(1)
		print(imageName)
		
getImage()


	



