\name{rLSgetScenarioModel}
\alias{rLSgetScenarioModel}

\title{Get a copy of the scenario model.}

\description{
 R interface function for LINDO API function \code{LSgetScenarioModel}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetScenarioModel(model,jScenario)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{jScenario}{An integer specifying the scenario to retrieve.}
 }

\value{
 If successful, rLSgetScenarioModel returns a LINDO API model object; 
 Otherwise, it returns NULL.
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
