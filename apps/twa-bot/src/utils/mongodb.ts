import mongoose from 'mongoose';
export * from 'mongodb';

async function mongoConnector(uri: string) {
  try {
    await mongoose.connect(uri);
    console.log('Successfuly connected MongoDB');
  } catch (error) {
    mongoose.connection.close();

    throw error;
  }
}

export async function connectToDatabase(url: string): ReturnType<typeof mongoConnector> {
  if (global.mongo) {
    return global.mongo;
  }

  if (!url) {
    throw new Error('Please define the MONGO_URL environment variable inside .env file');
  }

  const mongo = await mongoConnector(url);

  global.mongo = mongo;

  return mongo;
}
