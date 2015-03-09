# PhraseFrequencyAnalysis
Taking as input a relatively large body of text, analyze frequency of ordered phrases (ranked within categories based on number of words per phrase), i.e. most common 3 word phrase vs. most common 4 word phrase, etc.

Considerations:
-weights are assigned based on ordered word pairs
-punctuation are terminators
-ignore proper nouns

-MAKE SURE THERE ARE NO CYCLES

post-processing:
?-dynamically sort the edges based on number of edges (ie, heaviest 3 term phrase), as terms are added to graph
?-statically sort them in buckets (ie. 0-10 weight, 11-20 weight)
