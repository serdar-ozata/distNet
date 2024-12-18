import pandas as pd
from sklearn.preprocessing import LabelEncoder, MinMaxScaler

def preprocess_data(file_path):
    data = pd.read_csv(file_path)

    categorical_columns = ['Gender', 'Customer Type', 'Type of Travel', 'Class', 'Satisfaction']
    label_encoders = {}
    for col in categorical_columns:
        le = LabelEncoder()
        data[col] = le.fit_transform(data[col])
        label_encoders[col] = le

    data['Satisfaction'] = data['Satisfaction']

    numeric_columns = [
        'Age', 'Flight Distance', 'Departure Delay', 'Arrival Delay',
        'Departure and Arrival Time Convenience', 'Ease of Online Booking',
        'Check-in Service', 'Online Boarding', 'Gate Location',
        'On-board Service', 'Seat Comfort', 'Leg Room Service',
        'Cleanliness', 'Food and Drink', 'In-flight Service',
        'In-flight Wifi Service', 'In-flight Entertainment',
        'Baggage Handling'
    ]

    for col in numeric_columns:
        data[col] = pd.to_numeric(data[col], errors='coerce')

    data = data.drop(columns=['ID'], errors='ignore')

    # Normalize the numeric columns
    scaler = MinMaxScaler()
    data[numeric_columns] = scaler.fit_transform(data[numeric_columns])

    # Create separate CSVs
    satisfaction_data = data[['Satisfaction']]
    satisfaction_file_path = file_path.replace('.csv', '_y.csv')
    satisfaction_data.to_csv(satisfaction_file_path, index=False)

    remaining_data = data.drop(columns=['Satisfaction'], errors='ignore')
    remaining_file_path = file_path.replace('.csv', '_x.csv')
    remaining_data.to_csv(remaining_file_path, index=False)

    print(f"Satisfaction data saved to {satisfaction_file_path}")
    print(f"Remaining data saved to {remaining_file_path}")

    return data, label_encoders

if __name__ == '__main__':
    data, label_encoders = preprocess_data('data/airline_passenger_satisfaction.csv')
    print(data.head())
    print(label_encoders)