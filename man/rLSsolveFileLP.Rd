\name{rLSsolveFileLP}
\alias{rLSsolveFileLP}

\title{Optimizes a large LP from an MPS file.}

\description{
 R interface function for LINDO API function \code{LSsolveFileLP}. For more information,
 please refer to LINDO API User Manual.
}

\details{
 This routine is appropriate only for LP models with many more columns, 
 e.g., millions, than rows. It is appropriate for LP's that might otherwise
 not easily fit into available memory.
}

\usage{
rLSsolveFileLP(model,szFileNameMPS,szFileNameSol,nNoOfColsEvaluatedPerSet,
               nNoOfColsSelectedPerSet,nTimeLimitSec)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{szFileNameMPS}{The path and name of the input MPS file.}
 \item{szFileNameSol}{The path and name of the output solution file.}
 \item{nNoOfColsEvaluatedPerSet}{Number of columns evaluated together in one set.}
 \item{nNoOfColsSelectedPerSet}{Number of columns selected from one set.}
 \item{nTimeLimitSec}{Time limit for the program in seconds.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnSolStatusParam}{The status of the optimization.}
 \item{pnNoOfConsMps}{Number of constraints in the problem.}
 \item{pnNoOfColsMps}{Number of variables (columns) in the problem.}
 \item{pnErrorLine}{Line number at which a structural error was found.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
