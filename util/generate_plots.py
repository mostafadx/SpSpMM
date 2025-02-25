import matplotlib.pyplot as plt
import numpy as np

with open('../artifacts/results/results.txt','r') as file:
    restults = file.read()
    
restults = restults.replace(" nanoseconds",'')
restults_array = []
for ra in [ r.split('\n')[:-1]  for r in restults.split('--------------------------------------')[:-1]]:
  restults_array.append([float(t.split(' ')[-1 ]) for t in ra  if t != '' ])

scipy_resutls = restults_array[:21]
spdb_results = restults_array[21:42]
taco_results = restults_array[42:63]
baseline_results = restults_array[63:84]

(scipy_resutls).sort(key=lambda x:(x[3],x[1]))
(spdb_results).sort(key=lambda x:(x[3],x[1]))
(taco_results).sort(key=lambda x:(x[3],x[1]))
(baseline_results).sort(key=lambda x:(x[3],x[1]))

# Data provided by the user
sparsity_factors = ['1e-05', '1e-06', '1e-07']
scipy_times = [scipy_resutls[-1][0]/10e9, scipy_resutls[-2][0]/10e9, scipy_resutls[-3][0]/10e9]  # converting ms to s for consistency
baseline_SpDB_times = [spdb_results[-1][0]/10e9, spdb_results[-2][0]/10e9, spdb_results[-3][0]/10e9]  # converting ms to s
taco_times =  [taco_results[-1][0]/10e9, taco_results[-2][0]/10e9, taco_results[-3][0]/10e9]  # converting ms to s
baseline_times =  [baseline_results[-1][0]/10e9, baseline_results[-2][0]/10e9, baseline_results[-3][0]/10e9]  # np.nan for timeout

# Set up the bar width
bar_width = 0.2

# Set up the index for the groups
r1 = np.arange(len(sparsity_factors))
r2 = [x + bar_width for x in r1]
r3 = [x + bar_width for x in r2]
r4 = [x + bar_width for x in r3]

# Create the bar plot
fig, ax = plt.subplots()
ax.bar(r1, scipy_times, color='blue', width=bar_width, edgecolor='grey', label='scipy')
ax.bar(r2, baseline_SpDB_times, color='orange', width=bar_width, edgecolor='grey', label='baseline+SpDB')
ax.bar(r3, taco_times, color='green', width=bar_width, edgecolor='grey', label='taco')
ax.bar(r4, baseline_times, color='red', width=bar_width, edgecolor='grey', label='baseline')

# Add labels, title and axes ticks
ax.set_xlabel('Sparsity Factor', fontweight='bold')
ax.set_ylabel('Time (s)', fontweight='bold')
ax.set_title('Performance Comparison with Different Sparsity Factors')
ax.set_xticks([r + bar_width for r in range(len(sparsity_factors))])
ax.set_xticklabels(sparsity_factors)
ax.set_yscale('log')
ax.set_ylim(0.00001, 1)  # Set limits for y-axis considering log scale

# Create legend & Show graphic
ax.legend()
plt.show()

plt.savefig("../artifacts/plots/fig1.pdf", format="pdf", bbox_inches="tight")


# Updated data provided by the user
# Converting all times to seconds for consistency
scipy_times = [scipy_resutls[2][0]/10e9, scipy_resutls[1][0]/10e9, scipy_resutls[0][0]/10e9]  # converting ms to s for consistency
baseline_SpDB_times = [spdb_results[2][0]/10e9, spdb_results[1][0]/10e9, spdb_results[0][0]/10e9]  # converting ms to s
taco_times =  [taco_results[2][0]/10e9, taco_results[1][0]/10e9, taco_results[0][0]/10e9]  # converting ms to s
baseline_times =  [baseline_results[-1][0]/10e9, baseline_results[-2][0]/10e9, baseline_results[-3][0]/10e9]  # np.nan for timeout

# Set up the index for the groups
r1 = np.arange(len(sparsity_factors))
r2 = [x + bar_width for x in r1]
r3 = [x + bar_width for x in r2]
r4 = [x + bar_width for x in r3]

# Create the bar plot with updated data
fig, ax = plt.subplots()
ax.bar(r1, scipy_times, color='blue', width=bar_width, edgecolor='grey', label='scipy')
ax.bar(r2, baseline_SpDB_times, color='orange', width=bar_width, edgecolor='grey', label='baseline+SpDB')
ax.bar(r3, taco_times, color='green', width=bar_width, edgecolor='grey', label='taco')
ax.bar(r4, baseline_times, color='red', width=bar_width, edgecolor='grey', label='baseline')

# Add labels, title and axes ticks
ax.set_xlabel('Sparsity Factor', fontweight='bold')
ax.set_ylabel('Time (s)', fontweight='bold')
ax.set_title('Performance Comparison with Different Sparsity Factors')
ax.set_xticks([r + bar_width for r in range(len(sparsity_factors))])
ax.set_xticklabels(sparsity_factors)
ax.set_yscale('log')
ax.set_ylim(1e-9, 1)  # Adjust the limits for y-axis considering log scale and the new data range

# Create legend & Show graphic
ax.legend()
plt.show()

plt.savefig("../artifacts/plots/fig2.pdf", format="pdf", bbox_inches="tight")

# New data provided by the user
# Converting all times to seconds for consistency
dimensions = ['250e3', '75e3', '20e3', '10e3']
scipy_times = [
    scipy_resutls[-1][0]/10e9,
    scipy_resutls[-10][0]/10e9,
    scipy_resutls[-16][0]/10e9,
    scipy_resutls[-19][0]/10e9
]
baseline_SpDB_times = [
    spdb_results[-1][0]/10e9,
    spdb_results[-10][0]/10e9,
    spdb_results[-16][0]/10e9,
    spdb_results[-19][0]/10e9
]
taco_times = [
    taco_results[-1][0]/10e9,
    taco_results[-10][0]/10e9,
    taco_results[-16][0]/10e9,
    taco_results[-19][0]/10e9
]
baseline_times = [
    baseline_results[-1][0]/10e9,
    baseline_results[-10][0]/10e9,
    baseline_results[-16][0]/10e9,
    baseline_results[-19][0]/10e9
]

# Set up the index for the groups
r1 = np.arange(len(dimensions))
r2 = [x + bar_width for x in r1]
r3 = [x + bar_width for x in r2]
r4 = [x + bar_width for x in r3]

# Create the bar plot with new data
fig, ax = plt.subplots()
ax.bar(r1, scipy_times, color='blue', width=bar_width, edgecolor='grey', label='scipy')
ax.bar(r2, baseline_SpDB_times, color='orange', width=bar_width, edgecolor='grey', label='baseline+SpDB')
ax.bar(r3, taco_times, color='green', width=bar_width, edgecolor='grey', label='taco')
ax.bar(r4, baseline_times, color='red', width=bar_width, edgecolor='grey', label='baseline')

# Add labels, title and axes ticks
ax.set_xlabel('Dimension', fontweight='bold')
ax.set_ylabel('Time (s)', fontweight='bold')
ax.set_title('Performance Comparison with Different Dimensions')
ax.set_xticks([r + bar_width for r in range(len(dimensions))])
ax.set_xticklabels(dimensions)
ax.set_yscale('log')
ax.set_ylim(1e-9, 1)  # Adjust the limits for y-axis considering log scale and the new data range

# Create legend & Show graphic
ax.legend()
plt.show()
plt.savefig("../artifacts/plots/fig3.pdf", format="pdf", bbox_inches="tight")

# New data provided by the user, converted to seconds for consistency
scipy_times = [
    scipy_resutls[-3][0]/10e9,
    scipy_resutls[-12][0]/10e9,
    scipy_resutls[-18][0]/10e9,
    scipy_resutls[-21][0]/10e9
]
baseline_SpDB_times = [
    spdb_results[-3][0]/10e9,
    spdb_results[-12][0]/10e9,
    spdb_results[-18][0]/10e9,
    spdb_results[-21][0]/10e9
]
taco_times = [
    taco_results[-3][0]/10e9,
    taco_results[-12][0]/10e9,
    taco_results[-18][0]/10e9,
    taco_results[-21][0]/10e9
]
baseline_times = [
    baseline_results[-3][0]/10e9,
    baseline_results[-12][0]/10e9,
    baseline_results[-18][0]/10e9,
    baseline_results[-21][0]/10e9
]

# Set up the index for the groups
r1 = np.arange(len(dimensions))
r2 = [x + bar_width for x in r1]
r3 = [x + bar_width for x in r2]
r4 = [x + bar_width for x in r3]

# Create the bar plot with new data
fig, ax = plt.subplots()
ax.bar(r1, scipy_times, color='blue', width=bar_width, edgecolor='grey', label='scipy')
ax.bar(r2, baseline_SpDB_times, color='orange', width=bar_width, edgecolor='grey', label='baseline+SpDB')
ax.bar(r3, taco_times, color='green', width=bar_width, edgecolor='grey', label='taco')
ax.bar(r4, baseline_times, color='red', width=bar_width, edgecolor='grey', label='baseline')

# Add labels, title and axes ticks
ax.set_xlabel('Dimension', fontweight='bold')
ax.set_ylabel('Time (s)', fontweight='bold')
ax.set_title('Performance Comparison with Different Dimensions')
ax.set_xticks([r + bar_width for r in range(len(dimensions))])
ax.set_xticklabels(dimensions)
ax.set_yscale('log')
ax.set_ylim(1e-9, 1)  # Adjust the limits for y-axis considering log scale and the new data range

# Create legend & Show graphic
ax.legend()
plt.show()

plt.savefig("../artifacts/plots/fig4.pdf", format="pdf", bbox_inches="tight")
