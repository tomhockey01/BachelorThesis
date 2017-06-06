import pandas as pd
import time
import csv

from PIL import Image

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
	data = pd.read_csv('DATALOGTEST/A_Edit_Days_Only_Test.CSV')

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
	for concept, standard, weight in zip(hour[4:7], standardString[4:7], weightString[4:7]):
		#print(concept, standard, weight)
		totalEnvironmentalScore += (concept * weight)
		
	conceptList.append(totalEnvironmentalScore)

	totalPhysicalScore = 0
	for concept, standard, weight in zip(hour[1:4], standardString[1:4], weightString[1:4]):
		#print(concept, standard, weight)
		totalPhysicalScore += (concept * weight)
	totalPhysicalScore += (totalEnvironmentalScore * environmentWeight)
	
	conceptList.append(totalPhysicalScore)

	totalMentalScore = 0
	for concept, standard, weight in zip(hour[7:9], standardString[7:9], weightString[7:9]):
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

string = ""
for hour in calculatedPercentagesList:
	print(hour)
	
	totals = calculateTotal(hour)
	print(totals)
	performance = calculatePerformance(totals)
	performance = (performance - (minPerformance)) / (maxPerformance - (minPerformance))
	for singlePercentage in hour:
		string += str(singlePercentage)
		string += ","
	string += str(performance)
	string += "\n"

with open("Output.csv", "w") as text_file:
	text_file.write(string)














