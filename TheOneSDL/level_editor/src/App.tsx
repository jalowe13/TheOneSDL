import React, { useState, useEffect } from "react";

import "./App.css";

function App() {
  // Constants
  const defaultLevelText = "No Level Selected";
  const inputType = "text";
  // Calls
  const mockSaveApi = (levelData: {
    name: string;
  }): Promise<{ success: boolean; message: string }> => {
    console.log("Attempting to save data (mock):", levelData);
    return new Promise((resolve, reject) => {
      // Simulate network delay (e.g., 1 second)
      // TODO: Implement into the C++ backend calls wise.
      setTimeout(() => {
        // Simulate a successful save
        if (levelData.name) {
          // Basic check if name exists
          console.log("Mock API: Save successful!");
          resolve({
            success: true,
            message: `Level '${levelData.name}' saved successfully.`,
          });
        } else {
          console.error("Mock API: Save failed - level name is empty.");
          reject({
            success: false,
            message: "Save failed: Level name cannot be empty.",
          });
        }
      }, 1000); // 1000 milliseconds
    });
  };
  // States
  const [LevelName, setLevelName] = useState(defaultLevelText);
  const [InputText, setInputText] = useState("");
  // Handlers
  const handleInputChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setInputText(e.target.value);
  };
  const handleSaveLevelName = (e: React.FormEvent<HTMLFormElement>) => {
    e.preventDefault();
    mockSaveApi({ name: LevelName });
    setLevelName(InputText);
  };

  // Effect to run and dependency array
  useEffect(() => {
    console.log(`Level updated to ${LevelName}`);
  }, [LevelName]);

  return (
    <div>
      <h1>Level Editor</h1>
      <h2>Status: {LevelName}</h2>
      <form onSubmit={handleSaveLevelName}>
        Level to Edit
        <input
          type={inputType}
          value={InputText}
          onChange={handleInputChange}
        />
        <button>Save</button>
      </form>
    </div>
  );
}

export default App;
